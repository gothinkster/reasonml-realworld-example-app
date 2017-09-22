'use strict';

var Jest         = require("bs-jest/lib/js/src/jest.js");
var Caml_array   = require("bs-platform/lib/js/caml_array.js");
var JsonRequests = require("../src/jsonRequests.js");

var errorsJson = "{\"errors\":{\"email\":[\"is invalid\"],\"password\":[\"is too short (minimum is 8 characters)\"]}}";

describe("New user request", (function () {
        Jest.test("should respond with a decoded error", (function () {
                var newUser = JsonRequests.parseNewUser(errorsJson);
                if (newUser.tag) {
                  return Jest.ExpectJs[/* toBeTruthy */26](Jest.ExpectJs[/* expect */0](/* true */1));
                } else {
                  return Jest.ExpectJs[/* toBeTruthy */26](Jest.ExpectJs[/* expect */0](/* false */0));
                }
              }));
        return Jest.test("should say the email is invalid", (function () {
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
      }));

exports.errorsJson = errorsJson;
/*  Not a pure module */
