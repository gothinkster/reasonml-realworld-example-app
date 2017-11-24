open Models;

let show = ReasonReact.stringToElement;

let profile_image = {|http://i.imgur.com/Qr71crq.jpg|};
let second_image = {|"http://i.imgur.com/N4VcUeJ.jpg"|};

type action =
  | TagsFetched(array(string))
  | ShowMyFeed
  | ShowGlobalFeed
  | ArticlesFetched(articleList);

type state = {
  myFeedDisplay: ReactDOMRe.style,
  globalFeedDisplay: ReactDOMRe.style,
  myFeedActiveClass: string,
  globalfeedActiveClass: string,
  tags: array(string),
  articles: array(article),
  articleCount: int
};

let initialState = () => {
  tags: [||],
  myFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
  globalFeedDisplay: ReactDOMRe.Style.make(~display="block", ()),
  myFeedActiveClass: "nav-link disabled",
  globalfeedActiveClass: "nav-link active",
  articles: [||],
  articleCount: 0
};

/* article page uses this decoder as well */
let decodeAuthor = (json) =>
  Json.Decode.{
    username: json |> field("username", string), 
    bio: json |> optional(field("bio", string)),
    image: json |> optional(field("image", string)), 
    following: json |> field("following", bool)
  };

let decodeArticles = (json) => {  
  Json.Decode.{
    slug: json |> field("slug", string),
    title: json |> field("title", string),
    description: json |> field("description", string),
    body: json |> field("body", string),
    tagList: [||], /* json |> field("tagList", array(string)) */
    createdAt: json |> field("createdAt", string),
    updatedAt: json |> field("updatedAt", string), 
    favorited: json |> field("favorited", bool),
    favoritesCount: json |> field("favoritesCount", int), 
    author: json |> field("author", decodeAuthor)
  };
};

let populateTags = (reduce) => {
  let reduceTags = (_status, jsonPayload) => {

    jsonPayload |> Js.Promise.then_((result) => {
      let parsedPopularTags = Js.Json.parseExn(result);
      let tags = Json.Decode.(parsedPopularTags |> field("tags", array(string)));
      reduce((_) => TagsFetched(tags), ());

      tags |> Js.Promise.resolve
    }) |> ignore;
  };
  JsonRequests.getPoplarTags(reduceTags) |> ignore;
};

let populateGlobalFeed = (reduce) => {
  let reduceFeed = (_state, jsonPayload) => {
    jsonPayload |> Js.Promise.then_((result) => {
      let parsedArticles = Js.Json.parseExn(result);
      Js.log(parsedArticles);
      let articleList = Json.Decode.{
        articles: parsedArticles |> field("articles", array(decodeArticles)),
        articlesCount: parsedArticles |> field("articlesCount", int)
      };
      
      reduce((_) => ArticlesFetched(articleList), ());
      articleList |> Js.Promise.resolve
    })
  };
  /* Get the right page if there are more than 10 articles */
  JsonRequests.getGlobalArticles(reduceFeed, Effects.getTokenFromStorage(), 10, 0) |> ignore;
};

let showMyFeed = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  reduce((_) => ShowMyFeed,());
};

let showGlobalFeed = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  populateGlobalFeed(reduce);
  reduce((_) => ShowGlobalFeed,());
};

let goToArticle = (router, articleCallback, article, event, {ReasonReact.state}) => {
  ReactEventRe.Mouse.preventDefault(event);
  articleCallback(article);
  DirectorRe.setRoute(router,"/article")
};

let renderTag = (index, tag) => {
  <a href="" key=(string_of_int(index)) className="tag-pill tag-default"> (show(tag)) </a>
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

let component = ReasonReact.reducerComponent("Home");

let make = (~articleCallback, ~router, _children) => {
  ...component,
  initialState: initialState,
  reducer: (action, state) =>
    switch action {
    | TagsFetched(tagList) => ReasonReact.Update({...state, tags: tagList})
    | ShowMyFeed => ReasonReact.Update({
      ...state,
      myFeedDisplay: ReactDOMRe.Style.make(~display="block", ()),
      globalFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
      myFeedActiveClass: "nav-link active",
      globalfeedActiveClass: "nav-link disabled"
    })
    | ShowGlobalFeed => ReasonReact.Update({
      ...state,
      myFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
      globalFeedDisplay: ReactDOMRe.Style.make(~display="block", ()),
      myFeedActiveClass: "nav-link disabled",
      globalfeedActiveClass: "nav-link active"
    })
    | ArticlesFetched(articleList) => ReasonReact.Update({
      ...state,
      articles: articleList.articles,
      articleCount: articleList.articlesCount
    })
    },
  didMount: (self) => {
    populateTags(self.reduce);
    populateGlobalFeed(self.reduce);
    ReasonReact.NoUpdate
  },
  render: (self) => {
    let {ReasonReact.state} = self;
    <div className="home-page">
      <div className="banner">
        <div className="container">
          <h1 className="logo-font"> (show("conduit")) </h1>
          <p> (show("A place to share your knowledge.")) </p>
        </div>
      </div>
      <div className="container page">
        <div className="row">
          <div className="col-md-9">
            <div className="feed-toggle">
              <ul className="nav nav-pills outline-active">
                <li className="nav-item">
                  <a className=(state.myFeedActiveClass) href="#" onClick=(self.handle(showMyFeed))> (show("Your Feed")) </a>
                </li>
                <li className="nav-item">
                  <a className=(state.globalfeedActiveClass) href="#" onClick=(self.handle(showGlobalFeed))> (show("Global Feed")) </a>
                </li>
              </ul>
            </div>
            <div className="article-preview" style=(state.myFeedDisplay)>
              <div className="article-meta">
                <a href="profile.html" />
                <div className="info">
                  <a href="" className="author"> (show("Eric Simons")) </a>
                  <span className="date"> (show("January 20th")) </span>
                </div>
                <button className="btn btn-outline-primary btn-sm pull-xs-right">
                  <i className="ion-heart" />
                  (show("29"))
                </button>
              </div>
              <a href="" className="preview-link">
                <h1> (show("How to build webapps that scale")) </h1>
                <p> (show("This is the description for the post.")) </p>
                <span> (show("Read more...")) </span>
              </a>
            </div>
            <div style=(state.globalFeedDisplay)>
              (Array.mapi(renderArticle(self.handle, router, articleCallback), state.articles) |> ReasonReact.arrayToElement)
            </div>
          </div>
          <div className="col-md-3">
            <div className="sidebar">
              <p> (show("Popular Tags")) </p>
              <div className="tag-list">
                (Array.mapi(renderTag,state.tags) |> ReasonReact.arrayToElement)
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  }
};
