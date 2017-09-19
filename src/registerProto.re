type action =
  | Hulk
  | Thor string;

type state = {
  hasValidationError: bool,
  validationError: string
};

let component = ReasonReact.reducerComponent "RegisterProto";

let trigger {ReasonReact.state: state, reduce} => 
  reduce (fun _event => Thor "test") state;

let sideEffect event => {
  Js.log "I can do a side effecet here before calling the reducer.";
  Js.log event;

  Thor "new value"
};

let make _children => {
  ...component,
  initialState: fun () => {hasValidationError: false, validationError: "Do I look to be in a gaming mood?"},  
  reducer: fun action _state => {
    switch action {
      | Thor attack => {
        Js.log ("Attack: " ^ attack);
        ReasonReact.Update {hasValidationError: true, validationError: attack}
      }
      | Hulk => ReasonReact.SideEffects (fun self => trigger self)
    };
  },
  render: fun {state, reduce} => 
    <div>      
      <div> (ReasonReact.stringToElement state.validationError) </div>
      <button 
        onClick=(reduce sideEffect) 
        className="btn btn-lg btn-primary pull-xs-right"> 
        (ReasonReact.stringToElement "Sign up") 
      </button>            
    </div>
};