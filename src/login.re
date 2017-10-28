let show = ReasonReact.stringToElement;

type state = {
  email: string,
  password: string,
  hasValidationError: bool,
  errorList: list string
};

type action =
  | Login (bool, list string)
  | EmailUpdate string
  | PasswordUpdate string
  | LoginPending;

let goToRegister router event => {
  ReactEventRe.Mouse.preventDefault event;
  DirectorRe.setRoute router "/register";
};

module Encode = {
  let encodeUserCredentials creds => {
    open! Json.Encode;
    object_ [("email", string creds.email), ("password", string creds.password)]
  };

  let user topLevelUser =>
    Json.Encode.(
      object_ [
        ("user", encodeUserCredentials topLevelUser)
      ]
    );
};

let updateEmail event => EmailUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value;
let updatePassword event => PasswordUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value;

let errorDisplayList state =>
  List.filter (fun errorMessage => String.length errorMessage > 0) state.errorList
  |> List.mapi (fun acc => fun errorMessage =>  <ul className="error-messages" key=(string_of_int acc) > <li> (show errorMessage) </li> </ul> );

let loginUser route event {ReasonReact.state: state, reduce} => {
  ReactEventRe.Mouse.preventDefault event;
  let reduceByAuthResult _status jsonPayload => {
    jsonPayload
    |> Js.Promise.then_ (fun json => {
      let newUser = JsonRequests.checkForErrors json;
      
      let updatedState = 
        switch newUser {
          | Some errors => {...state, hasValidationError: true, errorList: errors |> JsonRequests.convertErrorsToList} 
          | None => {
            /* Parse user from request to save the token */
            DirectorRe.setRoute route "/home";
            {...state, hasValidationError: false}
          }
        };  
      reduce (fun _payload => Login (updatedState.hasValidationError, updatedState.errorList)) ()
      |> Js.Promise.resolve })
  };
  JsonRequests.authenticateUser reduceByAuthResult (Encode.user state) |> ignore;
  reduce (fun _ => LoginPending) ()
};

let component = ReasonReact.reducerComponent "Login";
let make ::router _children => {
  {
  ...component,
  initialState: fun () => {email: "", password: "", hasValidationError: false, errorList: []},
  reducer: fun action state => {
    switch action {
      | EmailUpdate value => ReasonReact.Update {...state, email: value}
      | PasswordUpdate value => ReasonReact.Update {...state, password: value}
      | Login (hasError, errorList) => {
        Js.log {j|Reducer call with error list: $errorList|j};
        ReasonReact.Update {...state, hasValidationError: hasError, errorList: errorList }}
      | LoginPending => {
        Js.log "getting set to pending";
        ReasonReact.NoUpdate}
  }},
  render: fun self => {
    let {ReasonReact.state: state, reduce} = self;
    {
    <div className="auth-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> (show "Sign in") </h1>
            <p className="text-xs-center"> <a href="#" onClick={goToRegister router}> (show "Need an account?") </a> </p>
            ( if state.hasValidationError {
              Array.of_list (errorDisplayList state) |> ReasonReact.arrayToElement;
            } else {
              ReasonReact.nullElement
            })
            <form>
              <fieldset className="form-group">
                <input
                  _type="text"
                  className="form-control form-control-lg"
                  placeholder="Email"
                  value=state.email
                  onChange=(reduce updateEmail)
                />
              </fieldset>
              <fieldset className="form-group">
                <input
                  _type="password"
                  className="form-control form-control-lg"
                  placeholder="Password"
                  value=state.password
                  onChange=(reduce updatePassword)
                />
              </fieldset>
              <button onClick=(self.handle (loginUser router) ) className="btn btn-lg btn-primary pull-xs-right"> (show "Sign in") </button>
            </form>
          </div>
        </div>
      </div>
    </div>}
    }
  }
};