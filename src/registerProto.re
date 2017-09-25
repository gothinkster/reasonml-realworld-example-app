type action =
  | Hulk
  | Thor string
  | Pending string;

type state = {
  hasError: bool,
  errorMessage: string
};

let component = ReasonReact.reducerComponent "RegisterProto";

let trigger {ReasonReact.state: state, reduce} => 
  reduce (fun _event => Thor "test") state;

let getRequest () => {
  open Register;

  {username: "", password: "", email: "", hasValidationError:false, errorList: []}
  |> Encode.user
};

let sideEffect {ReasonReact.state: _state, reduce} event => {
  ReactEventRe.Mouse.preventDefault event;

  let updateState _status jsonPayload => {
    jsonPayload 
    |> Js.Promise.then_ (fun _json => reduce (fun payload => Thor payload) ("this come back from promise") 
    |> Js.Promise.resolve)
  };
  JsonRequests.registerNewUser (updateState) (getRequest ()) |> ignore;

  Pending "Waiting for thor"
};

let make _children => {
  ...component,
  initialState: fun () => {hasError: false, errorMessage: "Do I look to be in a gaming mood?"},  
  reducer: fun action _state => {
    switch action { 
      | Thor attack => ReasonReact.Update {hasError: true, errorMessage: attack}
      | Hulk => ReasonReact.SideEffects (fun self => trigger self)
      | Pending message => ReasonReact.Update {hasError: true, errorMessage: message}
    };
  },
  render: fun self => {
    let {ReasonReact.state: state, reduce} = self; 
    {
    <div>      
      <div> (ReasonReact.stringToElement state.errorMessage) </div>
      <button 
        onClick=(reduce (sideEffect self)) 
        className="btn btn-lg btn-primary pull-xs-right"> 
        (ReasonReact.stringToElement "Sign up") 
      </button>            
    </div>
    }
  }  
};