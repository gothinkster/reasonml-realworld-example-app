'use strict';

var Jest         = require("bs-jest/lib/js/src/jest.js");
var JsonRequests = require("../src/jsonRequests.js");

var errorsJson = "{\"errors\":{\"email\":[\"is invalid\"],\"password\":[\"is too short (minimum is 8 characters)\"]}}";

describe("New user request", (function () {
        return Jest.test("should respond with a decoded error", (function () {
                      var newUser = JsonRequests.parseNewUser(errorsJson);
                      console.log(newUser);
                      var match = newUser[/* errors */0];
                      if (match) {
                        return Jest.ExpectJs[/* toBeTruthy */26](Jest.ExpectJs[/* expect */0](/* true */1));
                      } else {
                        return Jest.ExpectJs[/* toBeTruthy */26](Jest.ExpectJs[/* expect */0](/* false */0));
                      }
                    }));
      }));

var succesWithJson = "{\n  \"errors\":{\n    \"email\": null,\n    \"password\": null,\n    \"username\": null\n  },\n  \"user\":{\n    \"id\":12123,\n    \"email\":\"bryant@bryant.com\",\n    \"createdAt\":\"2017-09-23T09:35:16.686Z\",\n    \"updatedAt\":\"2017-09-23T09:35:16.691Z\",\n    \"username\":\"bryant\",\n    \"bio\":null,\n    \"image\":null,\n    \"token\":\"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpZCI6MTIxMjMsInVzZXJuYW1lIjoiYnJ5YW50IiwiZXhwIjoxNTExMzQzMzE2fQ.WpeiSLOW2UUYrgeC0cgPkLY5v7aUC7yNKcIVMClgfCw\"\n  }\n}";

exports.errorsJson     = errorsJson;
exports.succesWithJson = succesWithJson;
/*  Not a pure module */
