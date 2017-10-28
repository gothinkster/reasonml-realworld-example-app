open JsonRequests;

type action =
  | Login
  | Register((bool, list(string)))
  | NameUpdate(string)
  | EmailUpdate(string)
  | PasswordUpdate(string);

type state = {
  username: string,
  email: string,
  password: string,
  hasValidationError: bool,
  errorList: list(string)
};

module Encode = {
  let encodeUserCredentials = (creds) => {
    open! Json.Encode;
    object_([
      ("email", string(creds.email)),
      ("password", string(creds.password)),
      ("username", string(creds.username))
    ])
  };
  let user = (r) => Json.Encode.(object_([("user", encodeUserCredentials(r))]));
};

let component = ReasonReact.reducerComponent("Register");

let show = ReasonReact.stringToElement;

let register = (route, {ReasonReact.state, reduce}, event) => {
  ReactEventRe.Mouse.preventDefault(event);
  let jsonRequest = Encode.user(state);
  let updateState = (_status, jsonPayload) =>
    jsonPayload
    |> Js.Promise.then_(
         (json) => {
           let newUser = parseNewUser(json);
           let updatedState =
             switch newUser.errors {
             | Some(_user) =>
               DirectorRe.setRoute(route, "/home");
               {...state, hasValidationError: false}
             | None => {
                 ...state,
                 hasValidationError: true,
                 errorList: newUser |> Convert.toErrorListFromResponse
               }
             };
           reduce(
             (_payload) => Register((updatedState.hasValidationError, updatedState.errorList)),
             "this came back from promise"
           )
           |> Js.Promise.resolve
         }
       );
  JsonRequests.registerNewUser(updateState, jsonRequest) |> ignore;
  Register((false, ["Hitting server."]))
};

let goToLogin = (router, event) => {
  ReactEventRe.Mouse.preventDefault(event);
  DirectorRe.setRoute(router, "/login")
};

let login = (_event) => Login;

let updateName = (event) =>
  NameUpdate(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);

let updateEmail = (event) =>
  EmailUpdate(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);

let updatePassword = (event) =>
  PasswordUpdate(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value);

let errorDisplayList = (state) =>
  List.filter((errorMessage) => String.length(errorMessage) > 0, state.errorList)
  |> List.mapi(
       (acc, errorMessage) =>
         <ul className="error-messages" key=(string_of_int(acc))>
           <li> (show(errorMessage)) </li>
         </ul>
     );

/* TODO: use the route to go the next home screen when registered successfully */
let make = (~router, _children) => {
  ...component,
  initialState: () => {
    username: "",
    email: "",
    password: "",
    hasValidationError: false,
    errorList: []
  },
  reducer: (action, state) =>
    switch action {
    | NameUpdate(value) => ReasonReact.Update({...state, username: value})
    | EmailUpdate(value) => ReasonReact.Update({...state, email: value})
    | PasswordUpdate(value) => ReasonReact.Update({...state, password: value})
    | Login => ReasonReact.NoUpdate
    | Register((hasError, errorList)) =>
      ReasonReact.Update({...state, hasValidationError: hasError, errorList})
    },
  render: (self) => {
    let {ReasonReact.state, reduce} = self;
    <div className="auth-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> (show("Sign up")) </h1>
            <p className="text-xs-center">
              <a href="#" onClick=(goToLogin(router))> (show("Have an account?")) </a>
            </p>
            (
              if (state.hasValidationError) {
                Array.of_list(errorDisplayList(state)) |> ReasonReact.arrayToElement
              } else {
                ReasonReact.nullElement
              }
            )
            <form>
              <fieldset className="form-group">
                <input
                  _type="text"
                  className="form-control form-control-lg"
                  placeholder="Your Name"
                  value=state.username
                  onChange=(reduce(updateName))
                />
              </fieldset>
              <fieldset className="form-group">
                <input
                  _type="text"
                  className="form-control form-control-lg"
                  placeholder="Email"
                  value=state.email
                  onChange=(reduce(updateEmail))
                />
              </fieldset>
              <fieldset className="form-group">
                <input
                  _type="password"
                  className="form-control form-control-lg"
                  placeholder="Password"
                  value=state.password
                  onChange=(reduce(updatePassword))
                />
              </fieldset>
              <button
                onClick=(reduce(register(router, self)))
                className="btn btn-lg btn-primary pull-xs-right">
                (show("Sign up"))
              </button>
            </form>
          </div>
        </div>
      </div>
    </div>
  }
};
