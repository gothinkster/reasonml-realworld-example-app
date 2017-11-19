let show = ReasonReact.stringToElement;

let profile_image = {|http://i.imgur.com/Qr71crq.jpg|};

let second_image = {|"http://i.imgur.com/N4VcUeJ.jpg"|};

type action =
  | TagsFetched(array(string))
  | ShowMyFeed
  | ShowGlobalFeed;

type state = {
  myFeedDisplay: ReactDOMRe.style,
  globalFeedDisplay: ReactDOMRe.style,
  myFeedActiveClass: string,
  globalfeedActiveClass: string,
  tags: array(string)
};

let initialState = () => {
  tags: [||],
  myFeedDisplay: ReactDOMRe.Style.make(~display="none", ()),
  globalFeedDisplay: ReactDOMRe.Style.make(~display="block", ()),
  myFeedActiveClass: "nav-link disabled",
  globalfeedActiveClass: "nav-link active"
};

let renderTag = (index, tag) => {
  <a href="" key=(string_of_int(index)) className="tag-pill tag-default"> (show(tag)) </a>
};

let populateTags = (reduce) => {
  let reduceTags = (_status, jsonPayload) => {
    
    jsonPayload |> Js.Promise.then_((result) => {
      let parsedPopularTags = Js.Json.parseExn(result);
      let tags = Json.Decode.(parsedPopularTags |> field("tags", array(string)));
      Js.log(Array.length(tags));
      reduce((_) => TagsFetched(tags), ());

      tags |> Js.Promise.resolve
    }) |> ignore;
  };
  JsonRequests.getPoplarTags(reduceTags) |> ignore;
};

let populateGlobalFeed = (reduce) => {
  let reduceFeed = (_state, jsonPayload) => {
    jsonPayload |> Js.Promise.then_((result) => {
      Js.log(result);
      result |> Js.Promise.resolve
    })
  };
  /* Get the right page if there are more than 10 articles */
  JsonRequests.getGlobalArticles(reduceFeed, Effects.getTokenFromStorage(), 10, 0) |> ignore;
};

let showMyFeed = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  populateGlobalFeed(reduce); 
  reduce((_) => ShowMyFeed,());
};

let showGlobalFeed = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  reduce((_) => ShowGlobalFeed,());
};

let component = ReasonReact.reducerComponent("Home");

let make = (_children) => {
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
    },
  didMount: (self) => {
    populateTags(self.reduce);
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
            <div className="article-preview" style=(state.globalFeedDisplay)>
              <div className="article-meta">
                <a href="profile.html" />
                <div className="info">
                  <a href="" className="author"> (show("Albert Pai")) </a>
                  <span className="date"> (show("January 20th")) </span>
                </div>
                <button className="btn btn-outline-primary btn-sm pull-xs-right">
                  <i className="ion-heart" />
                  (show("32"))
                </button>
              </div>
              <a href="" className="preview-link">
                <h1>
                  (show("The song you won't ever stop singing. No matter how hard you try."))
                </h1>
                <p> (show("This is the description for the post.")) </p>
                <span> (show("Read more...")) </span>
              </a>
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
