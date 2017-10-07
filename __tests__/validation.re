open Jest;
open JsonRequests;
open Convert;
open Models;

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
        let errorGraph = { 
          errors : { 
            email: Some [|"is invalid"|], 
            password: Some [|"is too short (minimum is 8 characters)"|],
            username: None
          } 
        };  
        let errorsList = toErrorListFromResponse errorGraph;    
        
        expect (List.nth errorsList 0) |> toBe "Email is invalid";
      });  
      
      test "should properly parse a successful registration" (fun () => {
        let newUser = parseNewUser successJson;
        Js.log newUser;
        switch newUser {
          | Succeed user => expect user.id |> toBe 12123
          | Failed _message => expect 0 |> toEqual 1
        };
      })
    }); 
    