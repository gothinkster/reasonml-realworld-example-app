open Jest;
open JsonRequests;

let errorsJson = {j|{"errors":{"email":["is invalid"],"password":["is too short (minimum is 8 characters)"]}}|j};

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

      test "should say the email is invalid" (fun () => {
        let newUser = parseNewUser errorsJson;
        switch newUser {
          | Succeed _response => fail "Succeeded when it was suppose to fail"
          | Failed error => {
            switch error.errors.email {
              | Some address =>  expect (Array.get address 0) |> toEqual "is invalid" 
              | None => fail "Did not return email"
            };
          };
        };
      });

      test "should convert to error list" (fun () => {
        expect false |> toBeTruthy
      })
    }); 
    