open JsonRequests;

type action =
  | Login
  | Register
  | NameUpdate string
  | EmailUpdate string
  | PasswordUpdate string;

type state = {
  name: string,
  email: string,
  password: string,
  hasValidationError: bool,
  validationError: string,
  registrationSucceeded: bool
};

module Encode = {
  let encodeUserCredentials creds => {
    open! Json.Encode;
    object_ [("email", string creds.email), ("password", string creds.password)]
  };

  let user r =>
    Json.Encode.(
      object_ [
        ("user", encodeUserCredentials r )        
      ]
    );
}; 

let component = ReasonReact.reducerComponent "Register";

let show = ReasonReact.stringToElement;
let register _event => Register;
let login _event => Login;

let hideValidation = ReactDOMRe.Style.make display::"none" ();
let showValidation = ReactDOMRe.Style.make display::"block" ();

let updateName event => NameUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 
let updateEmail event => EmailUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 
let updatePassword event => PasswordUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 



let registrationResult status json => {       
  /* TODO: Make call to save token */  
  /*
  {
  "errors":{
      "body": [
        "can't be empty"
      ]
    }
  }
  */

  
  
  let saveToLocalStorage reply => {    
    Js.log reply;
    () |> Js.Promise.resolve;
  };

  json |> Js.Promise.then_ saveToLocalStorage |> ignore;
};

let registerNewUser credentials _route => Encode.user credentials |> JsonRequests.registerNewUser registrationResult;

let maskOff currentState => {
  /* this is what will get returned to the reducer in the register */
  {...currentState, registrationSucceeded: false, validationError: "Username taken"}
};

let reducer router action state => 
  switch action {
    | NameUpdate value => ReasonReact.Update {...state, name: value} 
    | EmailUpdate value => ReasonReact.Update {...state, email: value}
    | PasswordUpdate value => ReasonReact.Update {...state, password: value}
    | Login => ReasonReact.NoUpdate
    /* | Register => ReasonReact.SideEffects (fun _self => registerNewUser state route) */
    | Register => ReasonReact.Update {maskOff state}
  };

/* If we need to unit test, then we can pass in the reducer with the side effect function already passed in */
/* TODO: use the route to go the next home screen when registered successfully */
let make ::route _children => {
  ...component,
  initialState: fun () => {name: "", email: "", password: "", hasValidationError: false, validationError: "", registrationSucceeded:false},
  reducer: reducer (route),       
  render: fun {state, reduce} =>
    <div className="auth-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> (show "Sign up") </h1>
            <p className="text-xs-center"> <a href=""> (show "Have an account?") </a> </p>
            <ul className="error-messages" style=(state.hasValidationError ? showValidation: hideValidation) > <li> (show state.validationError) </li> </ul>
            <form>
              <fieldset className="form-group">
                <input
                  _type="text"
                  className="form-control form-control-lg"
                  placeholder="Your Name"
                  value=state.name
                  onChange=(reduce updateName)
                />
              </fieldset>
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
              <button onClick=(reduce register) className="btn btn-lg btn-primary pull-xs-right"> (show "Sign up") </button>
            </form>
          </div>
        </div>
      </div>
    </div>
};