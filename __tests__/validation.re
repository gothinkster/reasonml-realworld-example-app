open Jest;
open JsonRequests;
open Convert;

let errorsJson = {j|{"errors":{"email":["is invalid"],"password":["is too short (minimum is 8 characters)"]}}|j};
let successJson = {j|{
  "user":{
    "id":12123,
    "email":"bryant@bryant.com",
    "createdAt":"2017-09-23T09:35:16.686Z",
    "updatedAt":"2017-09-23T09:35:16.691Z",
    "username":"bryant",
    "bio":null,
    "image":null,
    "token":"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpZCI6MTIxMjMsInVzZXJuYW1lIjoiYnJ5YW50IiwiZXhwIjoxNTExMzQzMzE2fQ.WpeiSLOW2UUYrgeC0cgPkLY5v7aUC7yNKcIVMClgfCw"
  }
}|j};

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

      test "should not have username in the error list" (fun () => {
        let newUser = parseNewUser errorsJson;
        switch newUser {
          | Succeed _response => fail ""
          | Failed error => {
            switch error.errors.username {
              | Some _username => fail "Username should not be included"
              | None => expect "" |> toBe "" /* The type has to match the fail cases (string) */
            };
          }
        };
      });

      test "should convert to error list" (fun () => {
              

        expect false |> toBeTruthy;
      });

      test "" (fun () => {
        expect false |> toBeTruthy;
      });
    }); 
    