'use strict';

var Jest         = require("bs-jest/lib/js/src/jest.js");
var List         = require("bs-platform/lib/js/list.js");
var Convert      = require("../src/convert.js");
var Caml_array   = require("bs-platform/lib/js/caml_array.js");
var Json_decode  = require("bs-json/lib/js/src/json_decode.js");
var JsonRequests = require("../src/jsonRequests.js");

var errorsJson = "{\"errors\":{\"email\":[\"is invalid\"],\"password\":[\"is too short (minimum is 8 characters)\"]}}";

var successJson = "{\n  \"user\":{\n    \"id\":12123,\n    \"email\":\"bryant@bryant.com\",\n    \"createdAt\":\"2017-09-23T09:35:16.686Z\",\n    \"updatedAt\":\"2017-09-23T09:35:16.691Z\",\n    \"username\":\"bryant\",\n    \"bio\":null,\n    \"image\":null,\n    \"token\":\"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpZCI6MTIxMjMsInVzZXJuYW1lIjoiYnJ5YW50IiwiZXhwIjoxNTExMzQzMzE2fQ.WpeiSLOW2UUYrgeC0cgPkLY5v7aUC7yNKcIVMClgfCw\"\n  }\n}";

var succesWithJson = "{\n  \"errors\":{\n    \"email\": null,\n    \"password\": null,\n    \"username\": null\n  },\n  \"user\":{\n    \"id\":12123,\n    \"email\":\"bryant@bryant.com\",\n    \"createdAt\":\"2017-09-23T09:35:16.686Z\",\n    \"updatedAt\":\"2017-09-23T09:35:16.691Z\",\n    \"username\":\"bryant\",\n    \"bio\":null,\n    \"image\":null,\n    \"token\":\"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpZCI6MTIxMjMsInVzZXJuYW1lIjoiYnJ5YW50IiwiZXhwIjoxNTExMzQzMzE2fQ.WpeiSLOW2UUYrgeC0cgPkLY5v7aUC7yNKcIVMClgfCw\"\n  }\n}";

describe("New user request", (function () {
        Jest.test("should respond with a decoded error", (function () {
                var newUser = JsonRequests.parseNewUser(errorsJson);
                if (newUser.tag) {
                  return Jest.ExpectJs[/* toBeTruthy */26](Jest.ExpectJs[/* expect */0](/* true */1));
                } else {
                  return Jest.ExpectJs[/* toBeTruthy */26](Jest.ExpectJs[/* expect */0](/* false */0));
                }
              }));
        Jest.test("should say the email is invalid", (function () {
                var newUser = JsonRequests.parseNewUser(errorsJson);
                if (newUser.tag) {
                  var match = newUser[0][/* errors */0][/* email */0];
                  if (match) {
                    return Jest.ExpectJs[/* toEqual */11]("is invalid")(Jest.ExpectJs[/* expect */0](Caml_array.caml_array_get(match[0], 0)));
                  } else {
                    return Jest.fail("Did not return email");
                  }
                } else {
                  return Jest.fail("Succeeded when it was suppose to fail");
                }
              }));
        Jest.test("should not have username in the error list", (function () {
                var newUser = JsonRequests.parseNewUser(errorsJson);
                if (newUser.tag) {
                  var match = newUser[0][/* errors */0][/* username */2];
                  if (match) {
                    return Jest.fail("Username should not be included");
                  } else {
                    return Jest.ExpectJs[/* toBe */1]("")(Jest.ExpectJs[/* expect */0](""));
                  }
                } else {
                  return Jest.fail("");
                }
              }));
        Jest.test("should convert to error list", (function () {
                var errorGraph = /* record */[/* errors : record */[
                    /* email : Some */[/* array */["is invalid"]],
                    /* password : Some */[/* array */["is too short (minimum is 8 characters)"]],
                    /* username : None */0
                  ]];
                var errorsList = Convert.toErrorListFromResponse(errorGraph);
                return Jest.ExpectJs[/* toBe */1]("Email is invalid")(Jest.ExpectJs[/* expect */0](List.nth(errorsList, 0)));
              }));
        Jest.test("should properly parse a successful registration", (function () {
                var newUser = JsonRequests.parseNewUser(successJson);
                if (newUser.tag) {
                  Jest.ExpectJs[/* toEqual */11](1)(Jest.ExpectJs[/* expect */0](0));
                } else {
                  Jest.ExpectJs[/* toBe */1](12123)(Jest.ExpectJs[/* expect */0](newUser[0][/* id */0]));
                }
                return Jest.ExpectJs[/* toBe */1]("")(Jest.ExpectJs[/* expect */0](""));
              }));
        return Jest.test("example parse", (function () {
                      var json = JSON.parse(succesWithJson);
                      var parseError = function () {
                        return /* record */[
                                /* email : None */0,
                                /* password : None */0,
                                /* username : None */0
                              ];
                      };
                      var parseUser = function (jsonToParse) {
                        return /* record */[
                                /* id */Json_decode.field("id", Json_decode.$$int, jsonToParse),
                                /* email */Json_decode.field("email", Json_decode.string, jsonToParse),
                                /* createdAt */Json_decode.field("createdAt", Json_decode.string, jsonToParse),
                                /* updatedAt */Json_decode.field("updatedAt", Json_decode.string, jsonToParse),
                                /* username */Json_decode.field("username", Json_decode.string, jsonToParse),
                                /* bio : None */0,
                                /* image : None */0,
                                /* token */Json_decode.field("token", Json_decode.string, jsonToParse)
                              ];
                      };
                      /* record */[
                        /* errors */Json_decode.optional((function (param) {
                                return Json_decode.field("errors", parseError, param);
                              }), json),
                        /* user */Json_decode.optional((function (param) {
                                return Json_decode.field("user", parseUser, param);
                              }), json)
                      ];
                      return Jest.ExpectJs[/* toBe */1]("")(Jest.ExpectJs[/* expect */0](""));
                    }));
      }));

exports.errorsJson     = errorsJson;
exports.successJson    = successJson;
exports.succesWithJson = succesWithJson;
/*  Not a pure module */
