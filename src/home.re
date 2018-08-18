open Models;
open Infix;

let show = ReasonReact.string;

type action =
  | TagsFetched(array(string))
  | ShowMyFeed
  | ShowGlobalFeed
  | ArticlesFetched(articleList)
  | MyArticlesFetched(articleList)
  | TagArticlesFetched(articleList)
  | ShowTagList(string)
  | FavoriteArticle(string, bool)
  | ArticlesByPage(int);

type state = {
  myFeedDisplay: ReactDOMRe.style,
  globalFeedDisplay: ReactDOMRe.style,
  tagFeedDisplay: ReactDOMRe.style,
  myFeedActiveClass: string,
  globalfeedActiveClass: string,
  tagFeedActiveClass: string,
  tags: array(string),
  articles: array(article),
  articleCount: int,
  showTagTab: bool,
  currentTagName: string,
  favoritedArticleSlug: string,
};

let initialState = () => {
  tags: [||],
  myFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
  globalFeedDisplay: ReactDOMRe.Style.make(~display="block", ()),
  tagFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
  myFeedActiveClass: "nav-link disabled",
  globalfeedActiveClass: "nav-link active",
  tagFeedActiveClass: "nav-link disabled",
  articles: [||],
  articleCount: 0,
  showTagTab: false,
  currentTagName: "",
  favoritedArticleSlug: "",
};

let showTaggedArticles = event =>
  ShowTagList(ReactEvent.Mouse.target(event)##innerText);

/* article page uses this decoder as well */
let decodeAuthor = json =>
  Json.Decode.{
    username: json |> field("username", string),
    bio: json |> optional(field("bio", string)),
    image: json |> optional(field("image", string)),
    following: json |> field("following", bool),
  };

let decodeArticles = json =>
  Json.Decode.{
    slug: json |> field("slug", string),
    title: json |> field("title", string),
    description: json |> field("description", string),
    body: json |> field("body", string),
    tagList: json |> field("tagList", array(string)),
    createdAt: json |> field("createdAt", string),
    updatedAt: json |> field("updatedAt", string),
    favorited: json |> field("favorited", bool),
    favoritesCount: json |> field("favoritesCount", int),
    author: json |> field("author", decodeAuthor),
  };

let populateTags = send => {
  let reduceTags = (_status, jsonPayload) =>
    jsonPayload
    |> Js.Promise.then_(result => {
         let parsedPopularTags = Js.Json.parseExn(result);
         let tags =
           Json.Decode.(parsedPopularTags |> field("tags", array(string)));
         send(TagsFetched(tags));
         tags |> Js.Promise.resolve;
       })
    |> ignore;
  JsonRequests.getPoplarTags(reduceTags) |> ignore;
};

let reduceFeed = (reduceToAction, _state, jsonPayload) =>
  jsonPayload
  |> Js.Promise.then_(result => {
       let parsedArticles = Js.Json.parseExn(result);
       let articleList =
         Json.Decode.{
           articles:
             parsedArticles |> field("articles", array(decodeArticles)),
           articlesCount: parsedArticles |> field("articlesCount", int),
         };
       reduceToAction(articleList);
       articleList |> Js.Promise.resolve;
     });

let populateGlobalFeed = (send, pageNumber) => {
  let reduceFunc = articleList => send(ArticlesFetched(articleList));
  /* Get the right page if there are more than 10 articles */
  JsonRequests.getGlobalArticles(
    reduceFeed(reduceFunc),
    Effects.getTokenFromStorage(),
    10,
    pageNumber * 10,
  )
  |> ignore;
};

let populateFeed = send => {
  let reduceFunc = articleList => send(MyArticlesFetched(articleList));
  JsonRequests.getFeed(Effects.getTokenFromStorage(), reduceFeed(reduceFunc))
  |> ignore;
};

let showMyFeed = (event, {ReasonReact.state: _state, send}) => {
  ReactEvent.Mouse.preventDefault(event);
  populateFeed(send);
  send(ShowMyFeed);
};

let showGlobalFeed = (event, {ReasonReact.state: _state, send}) => {
  ReactEvent.Mouse.preventDefault(event);
  populateGlobalFeed(send, 0);
  send(ShowGlobalFeed);
};

let goToArticle =
    (router, articleCallback, article, event, {ReasonReact.state: _state}) => {
  ReactEvent.Mouse.preventDefault(event);
  articleCallback(article);
  DirectorRe.setRoute(router, "/article");
};

let goToProfile = (router, event, {ReasonReact.state: _state}) => {
  ReactEvent.Mouse.preventDefault(event);
  DirectorRe.setRoute(router, "/profile");
};

let updateFavoritedCount = (articles, currentSlug) => {
  let updateCurrentArticle = article => {
    let incDecFavCount =
      fun
      | true => article.favoritesCount + 1
      | false => article.favoritesCount - 1;
    article.slug == currentSlug ?
      {
        ...article,
        favorited: !article.favorited,
        favoritesCount: incDecFavCount(!article.favorited),
      } :
      article;
  };
  Array.map(updateCurrentArticle, articles);
};

let renderTag = ({ReasonReact.state: _state, send}, index, tag) =>
  <a
    onClick={showTaggedArticles >> send}
    href="#"
    key={string_of_int(index)}
    className="tag-pill tag-default">
    {show(tag)}
  </a>;

let renderArticleTag = (index, tag) =>
  <li className="tag-default tag-pill tag-outline" key={string_of_int(index)}>
    {show(tag)}
  </li>;

let rec range = (a, b) =>
  if (a > b) {
    [];
  } else {
    [a, ...range(a + 1, b)];
  };

let renderPager =
    ({ReasonReact.state: _state, send, ReasonReact.handle}, articleCount) => {
  let pageRanges = articleCount / 10 |> range(1);
  let reduceArticles = (currentPageNumber, event, _self) => {
    ReactEvent.Mouse.preventDefault(event);
    send(ArticlesByPage(currentPageNumber));
  };
  /* Add the logic to highlight the current page */
  List.map(
    currentPageNumber =>
      <li
        className="page-item ng-scope" key={string_of_int(currentPageNumber)}>
        <a
          className="page-link ng-binding"
          href=""
          onClick={handle(reduceArticles(currentPageNumber))}>
          {show(string_of_int(currentPageNumber))}
        </a>
      </li>,
    pageRanges,
  )
  |> Array.of_list
  |> ReasonReact.array;
};

let displayImage =
  fun
  | Some(image) => image
  | None => "";

let renderArticle =
    (
      {ReasonReact.state: _state, send},
      handle,
      router,
      articleCallback,
      index,
      article,
    ) =>
  <div key={string_of_int(index)} className="article-preview">
    <div>
      <div className="article-meta">
        <a href="#" onClick={handle(goToProfile(router))}>
          <img src={displayImage(article.author.image)} />
        </a>
        <div className="info">
          <a
            href="#"
            onClick={handle(goToProfile(router))}
            className="author">
            {show(article.author.username)}
          </a>
          <span className="date">
            {
              show(
                Js.Date.fromString(article.createdAt) |> Js.Date.toDateString,
              )
            }
          </span>
        </div>
        <button
          className="btn btn-outline-primary btn-sm pull-xs-right"
          onClick={
            _ => send(FavoriteArticle(article.slug, article.favorited))
          }>
          <i className="ion-heart" />
          {show(string_of_int(article.favoritesCount))}
        </button>
      </div>
      <a
        href="#"
        onClick={handle(goToArticle(router, articleCallback, article))}
        className="preview-link">
        <h1> {show(article.title)} </h1>
        <p> {show(article.description)} </p>
        <span> {show("Read more...")} </span>
        <ul className="tag-list">
          {Array.mapi(renderArticleTag, article.tagList) |> ReasonReact.array}
        </ul>
      </a>
    </div>
  </div>;

let component = ReasonReact.reducerComponent("Home");

let make = (~articleCallback, ~router, _children) => {
  ...component,
  initialState,
  reducer: (action, state) =>
    switch (action) {
    | TagsFetched(tagList) => ReasonReact.Update({...state, tags: tagList})
    | ShowMyFeed =>
      ReasonReact.Update({
        ...state,
        myFeedDisplay: ReactDOMRe.Style.make(~display="block", ()),
        globalFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
        tagFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
        myFeedActiveClass: "nav-link active",
        globalfeedActiveClass: "nav-link disabled",
        tagFeedActiveClass: "nav-link disabled",
      })
    | ShowGlobalFeed =>
      ReasonReact.Update({
        ...state,
        myFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
        globalFeedDisplay: ReactDOMRe.Style.make(~display="block", ()),
        tagFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
        myFeedActiveClass: "nav-link disabled",
        globalfeedActiveClass: "nav-link active",
        tagFeedActiveClass: "nav-link disabled",
      })
    | ArticlesFetched(articleList) =>
      ReasonReact.Update({
        ...state,
        articles: articleList.articles,
        articleCount: articleList.articlesCount,
        tagFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
      })
    | MyArticlesFetched(articleList) =>
      ReasonReact.Update({
        ...state,
        articles: articleList.articles,
        articleCount: articleList.articlesCount,
      })
    | TagArticlesFetched(articleList) =>
      ReasonReact.Update({
        ...state,
        articles: articleList.articles,
        myFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
        globalFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
        tagFeedDisplay: ReactDOMRe.Style.make(~display="block", ()),
      })
    | ShowTagList(currentTagName) =>
      ReasonReact.UpdateWithSideEffects(
        {
          ...state,
          currentTagName,
          myFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
          globalFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
          tagFeedDisplay: ReactDOMRe.Style.make(~display="block", ()),
          myFeedActiveClass: "nav-link disabled",
          globalfeedActiveClass: "nav-link disabled",
          tagFeedActiveClass: "nav-link active",
        },
        (
          self => {
            let reduceFunc = articleList =>
              self.send(TagArticlesFetched(articleList));
            JsonRequests.getArticlesByTag(
              reduceFeed(reduceFunc),
              currentTagName,
              Effects.getTokenFromStorage(),
            )
            |> ignore;
          }
        ),
      )
    | FavoriteArticle(slug, isCurrentlyFav) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, articles: updateFavoritedCount(state.articles, slug)},
        (
          _self =>
            !isCurrentlyFav ?
              JsonRequests.favoriteArticle(
                Effects.getTokenFromStorage(),
                slug,
              )
              |> ignore :
              JsonRequests.unfavoriteArticle(
                Effects.getTokenFromStorage(),
                slug,
              )
              |> ignore
        ),
      )
    | ArticlesByPage(currentPage) =>
      ReasonReact.SideEffects(
        (
          self => {
            let reduceFunc = articleList =>
              self.send(ArticlesFetched(articleList));
            JsonRequests.getGlobalArticles(
              reduceFeed(reduceFunc),
              Effects.getTokenFromStorage(),
              10,
              currentPage * 10,
            )
            |> ignore;
          }
        ),
      )
    },
  didMount: self => {
    populateTags(self.send);
    populateGlobalFeed(self.send, 0);
  },
  render: self => {
    let {ReasonReact.state} = self;
    let currentTagName = state.currentTagName;
    <div className="home-page">
      <div className="banner">
        <div className="container">
          <h1 className="logo-font"> {show("conduit")} </h1>
          <p> {show("A place to share your knowledge.")} </p>
        </div>
      </div>
      <div className="container page">
        <div className="row">
          <div className="col-md-9">
            <div className="feed-toggle">
              <ul className="nav nav-pills outline-active">
                <li className="nav-item">
                  <a
                    className={state.myFeedActiveClass}
                    href="#"
                    onClick={self.handle(showMyFeed)}>
                    {show("Your Feed")}
                  </a>
                </li>
                <li className="nav-item">
                  <a
                    className={state.globalfeedActiveClass}
                    href="#"
                    onClick={self.handle(showGlobalFeed)}>
                    {show("Global Feed")}
                  </a>
                </li>
                <li className="nav-item" style={state.tagFeedDisplay}>
                  <a className={state.tagFeedActiveClass} href="#">
                    {show({j|#$currentTagName|j})}
                  </a>
                </li>
              </ul>
            </div>
            <div style={state.myFeedDisplay}>
              {
                Array.mapi(
                  renderArticle(self, self.handle, router, articleCallback),
                  state.articles,
                )
                |> ReasonReact.array
              }
            </div>
            <div style={state.globalFeedDisplay}>
              {
                Array.mapi(
                  renderArticle(self, self.handle, router, articleCallback),
                  state.articles,
                )
                |> ReasonReact.array
              }
            </div>
            <div style={state.tagFeedDisplay}>
              {
                Array.mapi(
                  renderArticle(self, self.handle, router, articleCallback),
                  state.articles,
                )
                |> ReasonReact.array
              }
            </div>
            <div>
              <nav>
                <ul className="pagination">
                  {renderPager(self, state.articleCount)}
                </ul>
              </nav>
            </div>
          </div>
          <div className="col-md-3">
            <div className="sidebar">
              <p> {show("Popular Tags")} </p>
              <div className="tag-list">
                {
                  Array.mapi(renderTag(self), state.tags) |> ReasonReact.array
                }
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>;
  },
};