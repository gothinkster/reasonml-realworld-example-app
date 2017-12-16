open Models;

let show = ReasonReact.stringToElement;

type state = {
  myArticles: array(article),
  favoriteArticles: array(article),
  showMyArticles: bool,
  showFavArticle: bool,
  username: string,
  bio: string,
  image: string,
  isMyArticleDisplay: ReactDOMRe.style,
  isFavArticleDisplay: ReactDOMRe.style,
  articles: array(article),
  myFeedActiveClass: string,
  favfeedActiveClass: string
};

let initialState = {
  myArticles: [||],
  favoriteArticles:[||],
  showMyArticles: true,
  showFavArticle: false,
  username: "",
  bio: "",
  isMyArticleDisplay: ReactDOMRe.Style.make(~display="block", ()),
  isFavArticleDisplay: ReactDOMRe.Style.make(~display="none", ()),
  myFeedActiveClass: "nav-link disabled",
  favfeedActiveClass: "nav-link active",
  articles: [||],
  image: ""
};

type action =
  | MyArticles (array(article))
  | FavoriteArticle (array(article))
  | NoData
  | PendingMyArticles
  | PendingFavoriteArticles
  | CurrentUserFetched ((string, string, string));


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
  Json.Decode.(jsonArticles |> field("articles", array(parseArticle)));
};

let reduceMyArtcles = (reduceFunc, _status, payload) => {
  payload |> Js.Promise.then_((result) => {
    let parsedArticles = Js.Json.parseExn(result);

    let articleList = Json.Decode.{
      articles: parsedArticles |> extractArticleList,
      articlesCount: parsedArticles |> field("articlesCount", int)
    };
    reduceFunc(articleList.articles);

    articleList |> Js.Promise.resolve;
  });

};

let clickMyArticles = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  let reduceFunc = (articles) => reduce((_) => MyArticles(articles),());

  JsonRequests.getMyArticles(reduceMyArtcles(reduceFunc), state.username, Effects.getTokenFromStorage())
  |> ignore;

  reduce((_) => PendingMyArticles, ())
};

let clickProfileSettings = (router, event, {ReasonReact.state: _state}) => {
  ReactEventRe.Mouse.preventDefault(event);
  DirectorRe.setRoute(router,"/settings")
};

let clickMyFavorites = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  let reduceFunc = (articles) => reduce((_) => FavoriteArticle(articles),());
  JsonRequests.getFavoritedArticles(reduceMyArtcles(reduceFunc), state.username, Effects.getTokenFromStorage())
  |> ignore;

  reduce((_) => PendingFavoriteArticles, ())
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

let displayImage =
  fun
  | Some(image) => image
  | None => "";

let renderArticle = (handle, router, articleCallback, isFavorites, index, article) =>
  <div key=(string_of_int(index)) className="article-preview">
    <div>
      <div className="article-meta">
        (if (isFavorites){
          <a href="profile.html"> <img src=(displayImage(article.author.image))/> </a>
        }else{
          <a href="#"/>
        })        
        <div className="info">
          <a href="" className="author"> (show(article.author.username)) </a>
          <span className="date"> (show(Js.Date.fromString(article.createdAt) |> Js.Date.toDateString)) </span>
        </div>
        <button className="btn btn-outline-primary btn-sm pull-xs-right">
          <i className="ion-heart" />
          (show(string_of_int(article.favoritesCount)))
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
      myArticles: articleList,
      myFeedActiveClass: "nav-link active",
      favfeedActiveClass: "nav-link disabled"
    })
    | FavoriteArticle(articleList) => ReasonReact.Update({
      ...state,
      isMyArticleDisplay: ReactDOMRe.Style.make(~display="none", ()),
      isFavArticleDisplay: ReactDOMRe.Style.make(~display="block", ()),
      favoriteArticles: articleList,
      myFeedActiveClass: "nav-link disabled",
      favfeedActiveClass: "nav-link active"
    })
    | CurrentUserFetched ((username, bio, image)) => ReasonReact.Update({ ...state, username: username, bio: bio, image: image })
    | NoData => ReasonReact.NoUpdate
    | PendingFavoriteArticles => ReasonReact.NoUpdate
    | PendingMyArticles => ReasonReact.NoUpdate
    },
  didMount: (self) => {
    let (username, bio, image) = Effects.getUserFromStorage();
    
    let currentUsername = getDefaultFieldFor(username);
    let currentBio = getDefaultFieldFor(bio);
    let currentImage = getDefaultFieldFor(image);
    let token = Effects.getTokenFromStorage();

    JsonRequests.getMyArticles(reduceByAuthArticles(self), currentUsername, token) |> ignore;
    self.reduce((_) => CurrentUserFetched((currentUsername, currentBio, currentImage)), ());
    ReasonReact.NoUpdate
  },
  render: (self) => {
    let {ReasonReact.state, reduce} = self;
    <div className="profile-page">
      <div className="user-info">
        <div className="container">
          <div className="row">
            <div className="col-xs-12 col-md-10 offset-md-1">
              <img src={state.image} className="user-img" />
              <h4> (show(state.username)) </h4>
              <p>
                (
                  show(state.bio)
                )
              </p>
              <button className="btn btn-sm btn-outline-secondary action-btn" onClick=(self.handle(clickProfileSettings(router)))>
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
                  <a className=(state.myFeedActiveClass) href="#" onClick=(self.handle(clickMyArticles))> (show("My Articles")) </a>
                </li>
                <li className="nav-item">
                  <a className=(state.favfeedActiveClass) href="#" onClick=(self.handle(clickMyFavorites))> (show("Favorited Articles")) </a>
                </li>
              </ul>
            </div>
            <div style=(state.isMyArticleDisplay)>
              {Array.mapi(renderArticle(self.handle, router, articleCallback, false), state.myArticles) |>  ReasonReact.arrayToElement}
            </div>
            <div style=(state.isFavArticleDisplay)>
              {Array.mapi(renderArticle(self.handle, router, articleCallback, true), state.favoriteArticles) |>  ReasonReact.arrayToElement}
            </div>
          </div>
        </div>
      </div>
    </div>
  }
};
