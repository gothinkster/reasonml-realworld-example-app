open Jest;
open JsonRequests;

let errorsJson = {j|{"errors":{"email":["is invalid"],"password":["is too short (minimum is 8 characters)"]}}|j};

let checkEmail email => {
  switch email {
    | Some address => address
    | None => ""
  };
};

let () =
  describe "New user request"
    ExpectJs.(fun () => {
      test "should respond with a decoded error" (fun () => {
        let newUser = parseNewUser errorsJson;
        switch newUser {
          | Succeed _response => expect false |> toBeTruthy
          | Failed _error => expect (true) |> toBeTruthy
        };
      });
    }); 
    