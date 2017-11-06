let show = ReasonReact.stringToElement;

type state = {
  myArticles: list(string),
  favoriteArticles: list(string),
  showMyArticles: bool,
  showFavArticle: bool,
  username: string,
  bio: string
};

let initialState = {
  myArticles: [], 
  favoriteArticles:[], 
  showMyArticles: true, 
  showFavArticle: false, 
  username: "", 
  bio: ""
};

type action =
  | MyArticles(list(string))
  | FavoriteArticle(list(string))
  | PendingArticle;

let clickMyArticles = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  reduce((_) => PendingArticle, ())
};

let clickMyFavorites = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  PendingArticle
};

let component = ReasonReact.reducerComponent("Profile");
let make = (_children) => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | MyArticles(_articleList) => ReasonReact.NoUpdate
    | FavoriteArticle(_articleList) => ReasonReact.NoUpdate
    | PendingArticle => ReasonReact.NoUpdate
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
                  <a className="nav-link active" href="" onClick=(self.handle(clickMyArticles))> (show("My Articles")) </a>
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
  }
};
