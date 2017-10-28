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
  describe(
    "New user request",
    ExpectJs.(
      () => {
        test(
          "should respond with a decoded error",
          () => {
            let newUser = parseNewUser(errorsJson);
            switch newUser.errors {
            | Some(_response) => expect(true) |> toBeTruthy
            | None => expect(false) |> toBeTruthy
            }
          }
        );
        test(
          "should have an invalid email",
          () => {
            let newUser = parseNewUser(errorsJson);
            switch newUser.errors {
            | Some(errorList) =>
              switch errorList.email {
              | Some(error) => expect(error[0]) |> toBe("is invalid")
              | None => fail("this has failed")
              }
            | None => fail("this has failed")
            }
          }
        );
        test(
          "should have an error where the password is too short",
          () => {
            let newUser = parseNewUser(errorsJson);
            switch newUser.errors {
            | Some(errorList) =>
              switch errorList.password {
              | Some(password) =>
                expect(password[0]) |> toBe("is too short (minimum is 8 characters)")
              | None => fail("Failed to check password validation")
              }
            | None => fail("Failed to return any errors")
            }
          }
        );
        test(
          "should have the correct username",
          () => Models.(parseNewUser(succesWithJson).user.username |> expect |> toBe("bryant"))
        );
        test(
          "should return an error graph",
          () => {
            let result = JsonRequests.checkForErrors(loginErrorResponse);
            switch result {
            | Some(_errorList) => expect(true) |> toBe(true)
            | None => expect(false) |> toBe(true)
            }
          }
        )
      }
    )
  );
