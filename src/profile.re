let component = ReasonReact.statelessComponent("Profile");

let show = ReasonReact.stringToElement;

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="profile-page">
      <div className="user-info">
        <div className="container">
          <div className="row">
            <div className="col-xs-12 col-md-10 offset-md-1">
              <img src={|http://i.imgur.com/Qr71crq.jpg|} className="user-img" />
              <h4> (show("Eric Simons")) </h4>
              <p>
                (
                  show(
                    "Cofounder @GoThinkster, lived in Aol's HQ for a few months, kinda looks like Peeta from the Hunger Games"
                  )
                )
              </p>
              <button className="btn btn-sm btn-outline-secondary action-btn">
                <i className="ion-plus-round" />
                (show("&nbsp;"))
                (show("Follow Eric Simons"))
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
                  <a className="nav-link active" href=""> (show("My Articles")) </a>
                </li>
                <li className="nav-item">
                  <a className="nav-link" href=""> (show("Favorited Articles")) </a>
                </li>
              </ul>
            </div>
            <div className="article-preview">
              <div className="article-meta">
                <a href="#/home"> <img src={|http://i.imgur.com/Qr71crq.jpg|} /> </a>
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
                <a href=""> <img src={|http://i.imgur.com/N4VcUeJ.jpg|} /> </a>
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
                <ul className="tag-list">
                  <li className="tag-default tag-pill tag-outline"> (show("Music")) </li>
                  <li className="tag-default tag-pill tag-outline"> (show("Song")) </li>
                </ul>
              </a>
            </div>
          </div>
        </div>
      </div>
    </div>
};
