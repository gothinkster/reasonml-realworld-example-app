open JsonRequests;

type action =
  | Login
  | Register
  | RegisterReponse string
  | NameUpdate string
  | EmailUpdate string
  | PasswordUpdate string;

type state = {
  username: string,
  email: string,
  password: string,
  hasValidationError: bool,
  validationError: string  
};

module Encode = {
  let encodeUserCredentials creds => {
    open! Json.Encode;
    object_ [("email", string creds.email), ("password", string creds.password), ("username", string creds.username)]
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
let register event => {
  ReactEventRe.Mouse.preventDefault event;
  Register;
};
let login _event => Login;

let hideValidation = ReactDOMRe.Style.make display::"none" ();
let showValidation = ReactDOMRe.Style.make display::"block" ();

let updateName event => NameUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 
let updateEmail event => EmailUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 
let updatePassword event => PasswordUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 

let registrationResult reduce status json => {         
  let saveToLocalStorage reply => {        
    Js.log reply;     
    () |> Js.Promise.resolve;
  };

  json |> Js.Promise.then_ (fun response => {
    reduce (fun () => RegisterReponse response);
    saveToLocalStorage response |> Js.Promise.resolve;
    /* reduce (fun () => RegisterReponse response) |> Js.Promise.resolve; */
  })  |> ignore;
};

let registerNewUser {ReasonReact.state: state, reduce} _route => {     
  Encode.user state |> JsonRequests.registerNewUser (registrationResult reduce) |> ignore;
}; 

/* If we need to unit test, then we can pass in the reducer with the side effect 
   function already passed in */

/* TODO: use the route to go the next home screen when registered successfully */
let make ::route _children => {
  {
  ...component,  
  initialState: fun () => {username: "", email: "", password: "", hasValidationError: false, validationError: "Drifting"},
  reducer: fun action state => {
    switch action {
      | NameUpdate value => ReasonReact.Update {...state, username: value} 
      | EmailUpdate value => ReasonReact.Update {...state, email: value}
      | PasswordUpdate value => ReasonReact.Update {...state, password: value}
      | Login => ReasonReact.NoUpdate
      | RegisterReponse response => { 
        Js.log ("Repsonse: " ^ response);
        ReasonReact.Update {...state, hasValidationError: true}
      }
      | Register => ReasonReact.SideEffects (fun self => registerNewUserPrototype self)       
  }},       
  render: fun {state, reduce} =>
    <div className="auth-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> (show "Sign up") </h1>
            <p className="text-xs-center"> <a href=""> (show "Have an account?") </a> </p>
            (show state.validationError)
            ( if state.hasValidationError {
              <ul className="error-messages" > <li> (show state.validationError) </li> </ul> 
            } else {
              ReasonReact.nullElement
            })            
            <form>
              <fieldset className="form-group">
                <input
                  _type="text"
                  className="form-control form-control-lg"
                  placeholder="Your Name"
                  value=state.username
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
    </div>}
};