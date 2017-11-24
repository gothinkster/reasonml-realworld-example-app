open Models;

type comment = {
  id: int,
  createdAt: string,
  updatedAt: string,
  body: string,
  author: author
};

type state = {
  slug: string,
  commentList: list(comment)
};

type action =
  | AddComment
  | DeleteComment
  | FetchComments;

let show = ReasonReact.stringToElement;
let component = ReasonReact.reducerComponent("Article");
let renderComment = (index, comment) => {
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
};

let make = (~router, ~article, _children) => {
  ...component,
  initialState: () => {slug: "", commentList: []},
  reducer: (action, state) =>
    switch action {
      | AddComment => ReasonReact.NoUpdate
      | DeleteComment => ReasonReact.NoUpdate
      | FetchComments => ReasonReact.NoUpdate
    },
  render: (self) =>
    <div className="article-page">
      <div className="banner">
        <div className="container">
          <h1> (show(article.title)) </h1>
          <div className="article-meta">
            <a href=""> <img src="http://i.imgur.com/Qr71crq.jpg" /> </a>
            <div className="info">
              <a href="" className="author"> (show(article.author.username)) </a>
              <span className="date"> (show(Js.Date.fromString(article.createdAt) |> Js.Date.toDateString)) </span>
            </div>
            <button className="btn btn-sm btn-outline-secondary">
              <i className="ion-plus-round" />
              (show(" "))
              (show(article.author.username))
              <span className="counter"> (show("(10)")) </span>
            </button>
            (ReasonReact.stringToElement("  "))
            <button className="btn btn-sm btn-outline-primary">
              <i className="ion-heart" />
              (ReasonReact.stringToElement(" "))
              (show("Favorite Post"))
              <span className="counter"> (show("(0)")) </span>
            </button>
          </div>
        </div>
      </div>
      <div className="container page">
        <div className="row article-content">
          <div className="col-md-12">
            <p>
              (show(article.body))
            </p>
          </div>
        </div>
        <hr />
        <div className="article-actions">
          <div className="article-meta">
            <a href="profile.html"> <img src="http://i.imgur.com/Qr71crq.jpg" /> </a>
            <div className="info">
              <a href="" className="author"> (show(article.author.username)) </a>
              <span className="date"> (show(Js.Date.fromString(article.createdAt) |> Js.Date.toDateString)) </span>
            </div>
            <button className="btn btn-sm btn-outline-secondary">
              <i className="ion-plus-round" />
              (show(" "))
              (show(article.author.username))
              <span className="counter"> (show("(0)")) </span>
            </button>
            (show(" "))
            <button className="btn btn-sm btn-outline-primary">
              <i className="ion-heart" />
              (ReasonReact.stringToElement(" "))
              (show("Favorite Post"))
              <span className="counter"> (show("(0)")) </span>
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
            (List.mapi(renderComment, self.state.commentList) |> Array.of_list |> ReasonReact.arrayToElement)
          </div>
        </div>
      </div>
    </div>
};
