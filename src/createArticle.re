open Infix;

type state = {
  title: string,
  description: string,
  articleBody: string,
  rawTags: string,
};

type action =
  | ArticleSubmitted
  | UpdateTitle(string)
  | UpdateDescription(string)
  | UpdateBody(string)
  | UpdateTags(string);

let parseTags = enteredTags => Js.String.split(",", enteredTags);

module Encode = {
  let newArticle = (articleDetails: state) =>
    Json.Encode.(
      object_([
        ("title", string(articleDetails.title)),
        ("description", string(articleDetails.description)),
        ("body", string(articleDetails.articleBody)),
        (
          "tagList",
          parseTags(articleDetails.rawTags) |> Json.Encode.stringArray,
        ),
      ])
    );
};

let submissionResponse = (_status, payload) =>
  payload |> Js.Promise.then_(result => Js.log(result) |> Js.Promise.resolve);

let submitNewArticle = (event, state, send) => {
  ReactEvent.Mouse.preventDefault(event);
  JsonRequests.submitNewArticle(
    submissionResponse,
    Encode.newArticle(state),
    Effects.getTokenFromStorage(),
  )
  |> ignore;
  send(ArticleSubmitted);
};

let updateTitle = event => UpdateTitle(ReactEvent.Form.target(event)##value);

let updateDescription = event =>
  UpdateDescription(ReactEvent.Form.target(event)##value);

let updateBody = event => UpdateBody(ReactEvent.Form.target(event)##value);

let updateTags = event => UpdateTags(ReactEvent.Form.target(event)##value);

/* TODO: Add validation for body and title to be required */
let component = ReasonReact.reducerComponent("CreateArticle");

let make = _children => {
  ...component,
  initialState: () => {
    title: "",
    description: "",
    articleBody: "",
    rawTags: "",
  },
  reducer: (action, state) =>
    switch (action) {
    | ArticleSubmitted =>
      ReasonReact.SideEffects((_self => ReasonReact.Router.push("/home")))
    | UpdateTitle(title) => ReasonReact.Update({...state, title})
    | UpdateDescription(description) =>
      ReasonReact.Update({...state, description})
    | UpdateBody(body) => ReasonReact.Update({...state, articleBody: body})
    | UpdateTags(tags) => ReasonReact.Update({...state, rawTags: tags})
    },
  render: self =>
    <div className="editor-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-10 offset-md-1 col-xs-12">
            <form>
              <fieldset>
                <fieldset className="form-group">
                  <input
                    type_="text"
                    className="form-control form-control-lg"
                    placeholder="Article Title"
                    value={self.state.title}
                    onChange={updateTitle >> self.send}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    type_="text"
                    className="form-control"
                    placeholder="What's this article about?"
                    value={self.state.description}
                    onChange={updateDescription >> self.send}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <textarea
                    className="form-control"
                    rows=8
                    placeholder="Write your article (in markdown)"
                    value={self.state.articleBody}
                    onChange={updateBody >> self.send}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    type_="text"
                    className="form-control"
                    placeholder="Enter tags"
                    value={self.state.rawTags}
                    onChange={updateTags >> self.send}
                  />
                  <div className="tag-list" />
                </fieldset>
                <button
                  className="btn btn-lg pull-xs-right btn-primary"
                  type_="button"
                  onClick={
                    event => submitNewArticle(event, self.state, self.send)
                  }>
                  {show("Publish Article")}
                </button>
              </fieldset>
            </form>
          </div>
        </div>
      </div>
    </div>,
};