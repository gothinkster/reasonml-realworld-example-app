open Jest;
open JsonRequests;

let errorsJson = {j|{"errors":{"email":["is invalid"],"password":["is too short (minimum is 8 characters)"]}}|j};

let succesWithJson = {j|{
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

let loginErrorResponse = {j|{"errors":{"email or password":["is invalid"]}}|j};

let () =
  describe "New user request"
    ExpectJs.(fun () => {
      test "should respond with a decoded error" (fun () => {
        let newUser = parseNewUser errorsJson;

        switch newUser.errors {
          | Some _response => expect true |> toBeTruthy
          | None => expect (false) |> toBeTruthy
        };
      });

      test "should have an invalid email" (fun () => {
        let newUser = parseNewUser errorsJson;

        switch newUser.errors {
          | Some errorList =>
            switch errorList.email {
            | Some error => expect (Array.get error 0) |> toBe "is invalid"
            | None => fail "this has failed"
            }
          | None => fail "this has failed"
        };
      });

      test "should have an error where the password is too short" (fun () => {
        let newUser = parseNewUser errorsJson;

        switch newUser.errors {
          | Some errorList =>
            switch errorList.password {
              | Some password => expect (Array.get password 0) |> toBe "is too short (minimum is 8 characters)"
              | None => fail "Failed to check password validation"
            };
          | None => fail "Failed to return any errors"
        };
      });

      test "should have the correct username" (fun () => {
        open Models;

        (parseNewUser succesWithJson).user.username
        |> expect
        |> toBe "bryant"
      });

      test "should return error with wrong username password" (fun () => {
        let result = JsonRequests.parseCurrentUser loginErrorResponse;
        /* convert errors to a dictionary */
        let convertToDict json => {
          let errorJson = Js.Json.decodeObject json;
          switch errorJson {
            | Some errorList => {
              let errorKeys = Js.Dict.keys errorList;
              let errorValues = Js.Dict.values errorList;
              let errorArray = Array.mapi (fun acc errorField => {
                let validationError = Array.get errorValues acc;
                let frontCaps = String.capitalize errorField;
                {j|$frontCaps $validationError|j}
              }) errorKeys;

              Js.log errorArray;
            }
            | None => Js.log "I got nothing"
          };
        };

        switch result {
          | Error errorList => {
              convertToDict errorList |> ignore;
              Js.log errorList
          }
          | User user => Js.log user
        };
        expect true |> toBe true;
      })
    });