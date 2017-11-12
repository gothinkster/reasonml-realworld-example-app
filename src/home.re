let show = ReasonReact.stringToElement;

let profile_image = {|http://i.imgur.com/Qr71crq.jpg|};

let second_image = {|"http://i.imgur.com/N4VcUeJ.jpg"|};

type action =
  | TagsFetched(array(string));

type state = {tags: array(string)};

let renderTag = (index, tag) => {  
  <a href="" key=(string_of_int(index)) className="tag-pill tag-default"> (show(tag)) </a>
};

let component = ReasonReact.reducerComponent("Home");

let make = (_children) => {
  ...component,
  initialState: () => {tags: [||]},
  reducer: (action, _state) =>
    switch action {
    | TagsFetched(tagList) => ReasonReact.Update({tags: tagList})
    },
  didMount: (self) => {
    let reduceTags = (_status, jsonPayload) => {
      
      jsonPayload |> Js.Promise.then_((result) => {
        let parsedPopularTags = Js.Json.parseExn(result);        
        let tags = Json.Decode.(parsedPopularTags |> field("tags", array(string)));
        Js.log(Array.length(tags));
        self.reduce((_) => TagsFetched(tags), ());
      
        tags |> Js.Promise.resolve
      }) |> ignore;
    };
    JsonRequests.getPoplarTags(reduceTags) |> ignore;

    ReasonReact.NoUpdate
  },
  render: (self) => {
    let {ReasonReact.state} = self;
    <div className="home-page">
    (ReasonReact.stringToElement(string_of_int(Array.length(state.tags))))
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
                  <a className="nav-link disabled" href=""> (show("Your Feed")) </a>
                </li>
                <li className="nav-item">
                  <a className="nav-link active" href=""> (show("Global Feed")) </a>
                </li>
              </ul>
            </div>
            <div className="article-preview">
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
            <div className="article-preview">
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
