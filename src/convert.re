open Models;

let formatError = (fieldName, value) => {
  let prependFieldName = (fieldName, fieldValue) => fieldName ++ (" " ++ fieldValue);
  switch value {
  | Some(message) =>
    Array.map((errorMessage) => prependFieldName(fieldName, errorMessage), message)
  | None => [|""|]
  }
};

let toErrorListFromResponse = (errorGraph) =>
  switch errorGraph.errors {
  | Some(errors) =>
    (formatError("Email", errors.email) |> Array.to_list)
    @ (formatError("Username", errors.username) |> Array.to_list)
    @ (formatError("Password", errors.password) |> Array.to_list)
  | None => []
  };
