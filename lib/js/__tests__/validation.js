'use strict';

var Jest         = require("bs-jest/lib/js/src/jest.js");
var Caml_array   = require("bs-platform/lib/js/caml_array.js");
var JsonRequests = require("../src/jsonRequests.js");

var errorsJson = "{\"errors\":{\"email\":[\"is invalid\"],\"password\":[\"is too short (minimum is 8 characters)\"]}}";

var succesWithJson = "{\n  \"user\":{\n    \"id\":12123,\n    \"email\":\"bryant@bryant.com\",\n    \"createdAt\":\"2017-09-23T09:35:16.686Z\",\n    \"updatedAt\":\"2017-09-23T09:35:16.691Z\",\n    \"username\":\"bryant\",\n    \"bio\":null,\n    \"image\":null,\n    \"token\":\"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpZCI6MTIxMjMsInVzZXJuYW1lIjoiYnJ5YW50IiwiZXhwIjoxNTExMzQzMzE2fQ.WpeiSLOW2UUYrgeC0cgPkLY5v7aUC7yNKcIVMClgfCw\"\n  }\n}";

describe("New user request", (function () {
        Jest.test("should respond with a decoded error", (function () {
                var newUser = JsonRequests.parseNewUser(errorsJson);
                var match = newUser[/* errors */0];
                if (match) {
                  return Jest.ExpectJs[/* toBeTruthy */26](Jest.ExpectJs[/* expect */0](/* true */1));
                } else {
                  return Jest.ExpectJs[/* toBeTruthy */26](Jest.ExpectJs[/* expect */0](/* false */0));
                }
              }));
        Jest.test("should have an invalid email", (function () {
                var newUser = JsonRequests.parseNewUser(errorsJson);
                var match = newUser[/* errors */0];
                if (match) {
                  var match$1 = match[0][/* email */0];
                  if (match$1) {
                    return Jest.ExpectJs[/* toBe */1]("is invalid")(Jest.ExpectJs[/* expect */0](Caml_array.caml_array_get(match$1[0], 0)));
                  } else {
                    return Jest.fail("this has failed");
                  }
                } else {
                  return Jest.fail("this has failed");
                }
              }));
        Jest.test("should have an error where the password is too short", (function () {
                var newUser = JsonRequests.parseNewUser(errorsJson);
                var match = newUser[/* errors */0];
                if (match) {
                  var match$1 = match[0][/* password */1];
                  if (match$1) {
                    return Jest.ExpectJs[/* toBe */1]("is too short (minimum is 8 characters)")(Jest.ExpectJs[/* expect */0](Caml_array.caml_array_get(match$1[0], 0)));
                  } else {
                    return Jest.fail("Failed to check password validation");
                  }
                } else {
                  return Jest.fail("Failed to return any errors");
                }
              }));
        return Jest.test("should have the correct username", (function () {
                      JsonRequests.parseNewUser(succesWithJson);
                      return Jest.ExpectJs[/* toBe */1]("")(Jest.ExpectJs[/* expect */0](""));
                    }));
      }));

exports.errorsJson     = errorsJson;
exports.succesWithJson = succesWithJson;
/*  Not a pure module */
