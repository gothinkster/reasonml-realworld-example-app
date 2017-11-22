let component = ReasonReact.statelessComponent("Article");

let show = ReasonReact.stringToElement;

let make = (~router, _children) => {
  ...component,
  render: (_self) =>
    <div className="article-page">
      <div className="banner">
        <div className="container">
          <h1> (show("How to build webapps that scale")) </h1>
          <div className="article-meta">
            <a href=""> <img src="http://i.imgur.com/Qr71crq.jpg" /> </a>
            <div className="info">
              <a href="" className="author"> (show("Eric Simons")) </a>
              <span className="date"> (show("January 20th")) </span>
            </div>
            <button className="btn btn-sm btn-outline-secondary">
              <i className="ion-plus-round" />
              (show(" "))
              (show("Follow Eric Simons"))
              <span className="counter"> (show("(10)")) </span>
            </button>
            (ReasonReact.stringToElement("  "))
            <button className="btn btn-sm btn-outline-primary">
              <i className="ion-heart" />
              (ReasonReact.stringToElement(" "))
              (show("Favorite Post"))
              <span className="counter"> (show("(29)")) </span>
            </button>
          </div>
        </div>
      </div>
      <div className="container page">
        <div className="row article-content">
          <div className="col-md-12">
            <p>
              (
                show(
                  "Web development technologies have evolved at an incredible clip over the past few years."
                )
              )
            </p>
            <h2 id="introducing-ionic"> (show("Introducing RealWorld.")) </h2>
            <p> (show("It's a great solution for learning how other frameworks work.")) </p>
          </div>
        </div>
        <hr />
        <div className="article-actions">
          <div className="article-meta">
            <a href="profile.html"> <img src="http://i.imgur.com/Qr71crq.jpg" /> </a>
            <div className="info">
              <a href="" className="author"> (show("Eric Simons")) </a>
              <span className="date"> (show("January 20th")) </span>
            </div>
            <button className="btn btn-sm btn-outline-secondary">
              <i className="ion-plus-round" />
              (show(" "))
              (show("Follow Eric Simons"))
              <span className="counter"> (show("(10)")) </span>
            </button>
            (show(" "))
            <button className="btn btn-sm btn-outline-primary">
              <i className="ion-heart" />
              (ReasonReact.stringToElement(" "))
              (show("Favorite Post"))
              <span className="counter"> (show("(29)")) </span>
            </button>
          </div>
        </div>
        <div className="row">
          <div className="col-xs-12 col-md-8 offset-md-2">
            <form className="card comment-form">
              <div className="card-block">
                <textarea className="form-control" placeholder="Write a comment..." rows=3 />
              </div>
              <div className="card-footer">
                <img src="http://i.imgur.com/Qr71crq.jpg" className="comment-author-img" />
                <button className="btn btn-sm btn-primary"> (show("Post Comment")) </button>
              </div>
            </form>
            <div className="card">
              <div className="card-block">
                <p className="card-text">
                  (show("With supporting text below as a natural lead-in to additional content."))
                </p>
              </div>
              <div className="card-footer">
                <a href="" className="comment-author">
                  <img src="http://i.imgur.com/Qr71crq.jpg" className="comment-author-img" />
                </a>
                (show(" "))
                <a href="" className="comment-author"> (show("Jacob Schmidt")) </a>
                <span className="date-posted"> (show("Dec 29th")) </span>
              </div>
            </div>
            <div className="card">
              <div className="card-block">
                <p className="card-text">
                  (show("With supporting text below as a natural lead-in to additional content."))
                </p>
              </div>
              <div className="card-footer">
                <a href="" className="comment-author">
                  <img src="http://i.imgur.com/Qr71crq.jpg" className="comment-author-img" />
                </a>
                (show(" "))
                <a href="" className="comment-author"> (show("Jacob Schmidt")) </a>
                <span className="date-posted"> (show("Dec 29th")) </span>
                <span className="mod-options">
                  <i className="ion-edit" />
                  <i className="ion-trash-a" />
                </span>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
};
