let show = ReasonReact.stringToElement;

type state = {
  title: string,
  description: string,
  articleBody: string,
  rawTags: string
};

type action =
  | ArticleSubmitted(DirectorRe.t)
  | UpdateTitle(string)
  | UpdateDescription(string)
  | UpdateBody(string)
  | UpdateTags(string);

let parseTags = (enteredTags) => Js.String.split(",", enteredTags);

module Encode = {
  let newArticle = (articleDetails: state) => {
    Json.Encode.(object_([
      ("title", string(articleDetails.title)),
      ("description", string(articleDetails.description)),
      ("body", string(articleDetails.articleBody)),
      ("tagList", parseTags(articleDetails.rawTags) |> Json.Encode.stringArray)
    ]));
  };
};

let submissionResponse = (_status, payload) => {
  payload |> Js.Promise.then_((result) => Js.log(result) |> Js.Promise.resolve)
};  

let submitNewArticle = (router, event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  JsonRequests.submitNewArticle(submissionResponse, Encode.newArticle(state) , Effects.getTokenFromStorage()) |> ignore;
  let reduceArticleSubmission = (_) => ArticleSubmitted(router);
  reduce(reduceArticleSubmission, ())
};

let updateTitle = (event) =>
  UpdateTitle(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);
let updateDescription = (event) =>
  UpdateDescription(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);
let updateBody = (event) =>
  UpdateBody(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);
let updateTags = (event) =>
  UpdateTags(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);

/* TODO: Add validation for body and title to be required */

let component = ReasonReact.reducerComponent("CreateArticle");
let make = (~router,_children) => {
  ...component,
  initialState: () => {title:"",description: "", articleBody: "", rawTags: ""},
  reducer: (action, state) =>
    switch action {
    | ArticleSubmitted(router) => ReasonReact.SideEffects((_self) => {
      DirectorRe.setRoute(router, "/home")
    })
    | UpdateTitle(title) => ReasonReact.Update({...state, title: title})
    | UpdateDescription(description) => ReasonReact.Update({...state, description: description})
    | UpdateBody(body) => ReasonReact.Update({...state, articleBody: body})
    | UpdateTags(tags) => ReasonReact.Update({...state, rawTags: tags})
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
                    onChange=(self.reduce(updateTitle))
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    _type="text"
                    className="form-control"
                    placeholder="What's this article about?"
                    value=(self.state.description)
                    onChange=(self.reduce(updateDescription))
                  />
                </fieldset>
                <fieldset className="form-group">
                  <textarea
                    className="form-control"
                    rows=8
                    placeholder="Write your article (in markdown)"
                    value=(self.state.articleBody)
                    onChange=(self.reduce(updateBody))
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input 
                    _type="text" 
                    className="form-control" 
                    placeholder="Enter tags" 
                    value=(self.state.rawTags) 
                    onChange=(self.reduce(updateTags))
                  />
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
