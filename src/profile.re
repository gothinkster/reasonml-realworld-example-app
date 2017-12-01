open Models;

let show = ReasonReact.stringToElement;

type state = {
  myArticles: list(article),
  favoriteArticles: list(article),
  showMyArticles: bool,
  showFavArticle: bool,
  username: string,
  bio: string,
  isMyArticleDisplay: ReactDOMRe.style,
  isFavArticleDisplay: ReactDOMRe.style,
  articles: array(article)
};

let initialState = {
  myArticles: [],
  favoriteArticles:[],
  showMyArticles: true,
  showFavArticle: false,
  username: "",
  bio: "",
  isMyArticleDisplay: ReactDOMRe.Style.make(~display="block", ()),
  isFavArticleDisplay: ReactDOMRe.Style.make(~display="none", ()),
  articles: [||]
};

type action =
  | MyArticles (list(article))
  | FavoriteArticle (list(string))
  | PendingArticle
  | NoData
  | CurrentUserFetched ((string, string));

let clickMyArticles = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  Js.log("Articles were clicked.");
  /* This will be in the promise */
  reduce((_) => MyArticles([]),());

  reduce((_) => PendingArticle, ())
};

let clickMyFavorites = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  /* This will be in the promise */
  reduce((_) => FavoriteArticle([]),());

  reduce((_) => PendingArticle, ())
};

let getDefaultFieldFor = (fieldName) =>
  switch fieldName {
    | Some(name) => name
    | None => ""
  };

  let decodeAuthor = (json) =>
  Json.Decode.{
    username: json |> field("username", string), 
    bio: json |> optional(field("bio", string)),
    image: json |> optional(field("image", string)), 
    following: json |> field("following", bool)
  };

let extractArticleList = (jsonArticles: Js.Json.t) => {  
  let parseArticle = (rawArticle) =>
    Json.Decode.{
      slug: rawArticle |> field("slug", string),
      title: rawArticle |> field("title", string),
      description: rawArticle |> field("description", string),
      body: rawArticle |> field("body", string),
      tagList: [||], 
      createdAt: rawArticle |> field("createdAt", string),
      updatedAt: rawArticle |> field("updatedAt", string), 
      favorited: rawArticle |> field("favorited", bool),
      favoritesCount: rawArticle |> field("favoritesCount", int), 
      author: rawArticle |> field("author", decodeAuthor)
      
    };
  Json.Decode.(jsonArticles |> field("articles", list(parseArticle)));
};

/* side effect */
let reduceByAuthArticles = ({ReasonReact.state, reduce}, _status, jsonPayload) =>  {
  jsonPayload |> Js.Promise.then_((payload) => {
    let jsonArticles = Js.Json.parseExn(payload);
    let articleCount = Json.Decode.(jsonArticles |> field("articlesCount", int));

    switch articleCount {
      | count when count > 0 => reduce((_) => MyArticles(extractArticleList(jsonArticles)), ())
      | _ => reduce((_) => NoData, ())
    };

    payload |> Js.Promise.resolve;
  });
};

/* These functions were copied from  */
let goToArticle = (router, articleCallback, article, event, {ReasonReact.state}) => {
  ReactEventRe.Mouse.preventDefault(event);
  articleCallback(article);
  DirectorRe.setRoute(router,"/article")
};

let renderArticle = (handle, router, articleCallback, index, article) =>
  <div key=(string_of_int(index)) className="article-preview">
    <div>
      <div className="article-meta">
        <a href="profile.html" />
        <div className="info">
          <a href="" className="author"> (show(article.author.username)) </a>
          <span className="date"> (show(Js.Date.fromString(article.createdAt) |> Js.Date.toDateString)) </span>
        </div>
        <button className="btn btn-outline-primary btn-sm pull-xs-right">
          <i className="ion-heart" />
          (show("0"))
        </button>
      </div>
      <a href="#" onClick=(handle(goToArticle(router, articleCallback, article))) className="preview-link">
        <h1>
          (show(article.title))
        </h1>
        <p> (show(article.description)) </p>
        <span> (show("Read more...")) </span>
      </a>
    </div>
  </div>;


let component = ReasonReact.reducerComponent("Profile");
let make = (~articleCallback, ~router, _children) => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | MyArticles(articleList) => ReasonReact.Update({
      ...state,
      isMyArticleDisplay: ReactDOMRe.Style.make(~display ="block",()),
      isFavArticleDisplay: ReactDOMRe.Style.make(~display="none", ()),
      myArticles: articleList
    })
    | FavoriteArticle(_articleList) => ReasonReact.Update({
      ...state,
      isMyArticleDisplay: ReactDOMRe.Style.make(~display="none", ()),
      isFavArticleDisplay: ReactDOMRe.Style.make(~display="block", ())
    })
    | CurrentUserFetched ((username, bio)) => ReasonReact.Update({ ...state, username: username, bio: bio })
    | PendingArticle => ReasonReact.NoUpdate
    | NoData => ReasonReact.NoUpdate
    },
  didMount: (self) => {
    let (username, bio) = Effects.getUserFromStorage();

    let currentUsername = getDefaultFieldFor(username);
    let currentBio = getDefaultFieldFor(bio);
    let token = Effects.getTokenFromStorage();

    JsonRequests.getMyArticles(reduceByAuthArticles(self), currentUsername, token) |> ignore;
    self.reduce((_) => CurrentUserFetched((currentUsername, currentBio)), ());
    ReasonReact.NoUpdate
  },
  render: (self) => {
    let {ReasonReact.state, reduce} = self;
    <div className="profile-page">
      <div className="user-info">
        <div className="container">
          <div className="row">
            <div className="col-xs-12 col-md-10 offset-md-1">
              <img src={|http://i.imgur.com/Qr71crq.jpg|} className="user-img" />
              <h4> (show(state.username)) </h4>
              <p>
                (
                  show(state.bio)
                )
              </p>
              <button className="btn btn-sm btn-outline-secondary action-btn">
                <i className="ion-plus-round" />
                (show("Edit Profile Settings"))
              </button>
            </div>
          </div>
        </div>
      </div>
      <div className="container">
        <div className="row">
          <div className="col-xs-12 col-md-10 offset-md-1">
            <div className="articles-toggle">
              <ul className="nav nav-pills outline-active">
                <li className="nav-item">
                  <a className="nav-link active" href="#" onClick=(self.handle(clickMyArticles))> (show("My Articles")) </a>
                </li>
                <li className="nav-item">
                  <a className="nav-link" href="#" onClick=(self.handle(clickMyFavorites))> (show("Favorited Articles")) </a>
                </li>
              </ul>
            </div>
            <div className="article-preview" style=(state.isMyArticleDisplay)>
              {List.mapi(renderArticle(self.handle, router, articleCallback), state.myArticles) |> Array.of_list |>  ReasonReact.arrayToElement}
            </div>
            <div className="article-preview" style=(state.isFavArticleDisplay)>

            </div>
          </div>
        </div>
      </div>
    </div>
  }
};
