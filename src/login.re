open Infix;

let show = ReasonReact.string;

type state = {
  email: string,
  password: string,
  hasValidationError: bool,
  errorList: list(string),
};

type action =
  | Login((bool, list(string)))
  | EmailUpdate(string)
  | PasswordUpdate(string)
  | LoginPending;

let goToRegister = (router, event) => {
  ReactEvent.Mouse.preventDefault(event);
  DirectorRe.setRoute(router, "/register");
};

module Encode = {
  let encodeUserCredentials = creds => {
    open! Json.Encode;
    object_([
      ("email", string(creds.email)),
      ("password", string(creds.password)),
    ]);
  };
  let user = topLevelUser =>
    Json.Encode.(object_([("user", encodeUserCredentials(topLevelUser))]));
  let currentUser = (username, bio) =>
    Json.Encode.[("username", string(username)), ("bio", string(bio))];
};

let updateEmail = event => EmailUpdate(ReactEvent.Form.target(event)##value);

let updatePassword = event =>
  PasswordUpdate(ReactEvent.Form.target(event)##value);

let errorDisplayList = state =>
  List.filter(
    errorMessage => String.length(errorMessage) > 0,
    state.errorList,
  )
  |> List.mapi((acc, errorMessage) =>
       <ul className="error-messages" key={string_of_int(acc)}>
         <li> {show(errorMessage)} </li>
       </ul>
     );

let loginUser = (route, event, {ReasonReact.state, send}) => {
  ReactEvent.Mouse.preventDefault(event);
  let reduceByAuthResult = (_status, jsonPayload) =>
    jsonPayload
    |> Js.Promise.then_(json => {
         let newUser = JsonRequests.checkForErrors(json);
         let updatedState =
           switch (newUser) {
           | Some(errors) => {
               ...state,
               hasValidationError: true,
               errorList: errors |> JsonRequests.convertErrorsToList,
             }
           | None =>
             let loggedIn = JsonRequests.parseNewUser(json);
             Effects.saveTokenToStorage(loggedIn.user.token);
             Effects.saveUserToStorage(
               ~username=loggedIn.user.username,
               ~bio=loggedIn.user.bio,
               ~image=loggedIn.user.image,
             );
             DirectorRe.setRoute(route, "/home");
             {...state, hasValidationError: false};
           };
         /* TODO: Create a reducer to do nothing with succesful login so the state doesn't try to update */
         send(
           Login((updatedState.hasValidationError, updatedState.errorList)),
         )
         |> Js.Promise.resolve;
       });
  JsonRequests.authenticateUser(reduceByAuthResult, Encode.user(state))
  |> ignore;
  send(LoginPending);
};

let component = ReasonReact.reducerComponent("Login");

let make = (~router, _children) => {
  ...component,
  initialState: () => {
    email: "",
    password: "",
    hasValidationError: false,
    errorList: [],
  },
  reducer: (action, state) =>
    switch (action) {
    | EmailUpdate(value) => ReasonReact.Update({...state, email: value})
    | PasswordUpdate(value) =>
      ReasonReact.Update({...state, password: value})
    | Login((hasError, errorList)) =>
      ReasonReact.Update({...state, hasValidationError: hasError, errorList})
    | LoginPending => ReasonReact.NoUpdate
    },
  render: self => {
    let {ReasonReact.state, send} = self;
    <div className="auth-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> {show("Sign in")} </h1>
            <p className="text-xs-center">
              <a href="#" onClick={goToRegister(router)}>
                {show("Need an account?")}
              </a>
            </p>
            {
              if (state.hasValidationError) {
                Array.of_list(errorDisplayList(state)) |> ReasonReact.array;
              } else {
                ReasonReact.null;
              }
            }
            <form>
              <fieldset className="form-group">
                <input
                  type_="text"
                  className="form-control form-control-lg"
                  placeholder="Email"
                  value={state.email}
                  onChange={updateEmail >> send}
                />
              </fieldset>
              <fieldset className="form-group">
                <input
                  type_="password"
                  className="form-control form-control-lg"
                  placeholder="Password"
                  value={state.password}
                  onChange={updatePassword >> send}
                />
              </fieldset>
              <button
                onClick={self.handle(loginUser(router))}
                className="btn btn-lg btn-primary pull-xs-right">
                {show("Sign in")}
              </button>
            </form>
          </div>
        </div>
      </div>
    </div>;
  },
};