let show = ReasonReact.stringToElement;

type state = {
  title: string,
  description: string,
  articleBody: string,
  rawTags: string
};

type action =
  | ArticleSubmitted(DirectorRe.t);

let submitNewArticle = (router, event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  let reduceArticleSubmission = (_) => ArticleSubmitted(router);
  reduce(reduceArticleSubmission, ())
};

let component = ReasonReact.reducerComponent("CreateArticle");
let make = (~router,_children) => {
  ...component,
  initialState: () => {title:"",description: "", articleBody: "", rawTags: ""},
  reducer: (action, _state) =>
    switch action {
    | ArticleSubmitted(router) => ReasonReact.SideEffects((_self) => {
      DirectorRe.setRoute(router, "/home")
    })
  },
  render: (self) =>
    <div className="editor-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-10 offset-md-1 col-xs-12">
            <form>
              <fieldset>
                <fieldset className="form-group">
                  <input
                    _type="text"
                    className="form-control form-control-lg"
                    placeholder="Article Title"
                    value=(self.state.title)
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    _type="text"
                    className="form-control"
                    placeholder="What's this article about?"
                    value=(self.state.description)
                  />
                </fieldset>
                <fieldset className="form-group">
                  <textarea
                    className="form-control"
                    rows=8
                    placeholder="Write your article (in markdown)"
                    value=(self.state.articleBody)
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input _type="text" className="form-control" placeholder="Enter tags" value=(self.state.rawTags) />
                  <div className="tag-list" />
                </fieldset>
                <button className="btn btn-lg pull-xs-right btn-primary" _type="button" onClick=(self.handle(submitNewArticle(router)))>
                  (show("Publish Article"))
                </button>
              </fieldset>
            </form>
          </div>
        </div>
      </div>
    </div>
};
