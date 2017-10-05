open Models;

let formatError fieldName value => {
  let prependFieldName fieldName fieldValue => fieldName ^ " " ^ fieldValue;
  switch value {
    | Some message => Array.map (fun errorMessage => prependFieldName fieldName errorMessage) message
    | None => [|""|]
  };
};

let toErrorListFromResponse errorGraph => {  
  Js.log errorGraph.errors;
  (formatError "Email" errorGraph.errors.email |> Array.to_list) @ 
  (formatError "Username" errorGraph.errors.username |> Array.to_list) @
  (formatError "Password" errorGraph.errors.password |> Array.to_list)
};