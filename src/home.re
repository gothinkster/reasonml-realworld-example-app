let component = ReasonReact.statelessComponent("Home");

let show = ReasonReact.stringToElement;

let profile_image = {|http://i.imgur.com/Qr71crq.jpg|};

let second_image = {|"http://i.imgur.com/N4VcUeJ.jpg"|};

let make = (_children) => {
  ...component,
  render: (_self) =>
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
                <a href="" className="tag-pill tag-default"> (show("programming")) </a>
                <a href="" className="tag-pill tag-default"> (show("javascript")) </a>
                <a href="" className="tag-pill tag-default"> (show("emberjs")) </a>
                <a href="" className="tag-pill tag-default"> (show("angularjs")) </a>
                <a href="" className="tag-pill tag-default"> (show("react")) </a>
                <a href="" className="tag-pill tag-default"> (show("mean")) </a>
                <a href="" className="tag-pill tag-default"> (show("node")) </a>
                <a href="" className="tag-pill tag-default"> (show("rails")) </a>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
};
