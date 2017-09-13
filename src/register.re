open Bs_fetch;

type action =
  | Login
  | Register
  | NameUpdate string
  | EmailUpdate string
  | PasswordUpdate string;

type state = {
  name: string,
  email: string,
  password: string
};

let component = ReasonReact.reducerComponent "Register";

let show = ReasonReact.stringToElement;
let register _event => Register;
let login _event => Login;

let hideMessage = ReactDOMRe.Style.make display::"none" ();

let updateName event => NameUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 
let updateEmail event => EmailUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 
let updatePassword event => PasswordUpdate (ReactDOMRe.domElementToObj (ReactEventRe.Form.target event))##value; 

/* TODO: Refactor this to be outside of the component */
let make_headers (token: option string) => {
  let content_type = ("content-type", "application/json");
  switch token {
  | None => [|content_type|]
  | Some t => [|content_type, ("authorization", "Token " ^ t)|]
  }
};

let make_init method_ token (data: option Js.Json.t) => {
  let default_init =        
    RequestInit.make mode::NoCORS ::method_ headers::(HeadersInit.makeWithArray @@ make_headers token);

  switch data {
  | None => default_init ()
  | Some d => default_init body::(BodyInit.make @@ Js.Json.stringify d) ()
  }
};

let toJson listedElements => {
  listedElements
  |> Js.Dict.fromList 
  |> Js.Json.object_;
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

type tesla = Js.t {
  .
  color: string
};

let loginUser credentials => {   
  open Config;   

  let data = Encode.user credentials; 
  let request = make_init Post None (Some data);  
  
  /* TODO: Changed the endpoint to the login endpoint */
  let result =  
    Js.Promise.(
      fetch (apiUrlBase ^ (mapUrl Tags))
      |> then_ Response.text
      |> then_ (fun text => print_endline text |> resolve)
    );
  Js.log(result);    
  ()
};

/* If we need to unit test, then we can pass in the reducer with the side effect function already passed in */
let make _children => {
  ...component,
  initialState: fun () => {name: "", email: "", password: ""},
  reducer: fun action state =>
    switch action {
    | NameUpdate value => ReasonReact.Update {...state, name: value} 
    | EmailUpdate value => ReasonReact.Update {...state, email: value}
    | PasswordUpdate value => ReasonReact.Update {...state, password: value}
    | Login => ReasonReact.NoUpdate
    | Register => ReasonReact.SideEffects (fun _self => loginUser state)
    },   
  render: fun {state, reduce} =>
    <div className="auth-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> (show "Sign up") </h1>
            <p className="text-xs-center"> <a href=""> (show "Have an account?") </a> </p>
            <ul className="error-messages" style=(hideMessage) > <li> (show "That email is already taken") </li> </ul>
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