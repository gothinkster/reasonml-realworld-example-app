'use strict';

var Jest         = require("bs-jest/lib/js/src/jest.js");
var JsonRequests = require("../src/jsonRequests.js");

var errorsJson = "{\"errors\":{\"email\":[\"is invalid\"],\"password\":[\"is too short (minimum is 8 characters)\"]}}";

function checkEmail(email) {
  if (email) {
    return email[0];
  } else {
    return "";
  }
}

describe("New user request", (function () {
        return Jest.test("should respond with a decoded error", (function () {
                      var newUser = JsonRequests.parseNewUser(errorsJson);
                      if (newUser.tag) {
                        return Jest.ExpectJs[/* toBeTruthy */26](Jest.ExpectJs[/* expect */0](/* true */1));
                      } else {
                        return Jest.ExpectJs[/* toBeTruthy */26](Jest.ExpectJs[/* expect */0](/* false */0));
                      }
                    }));
      }));

exports.errorsJson = errorsJson;
exports.checkEmail = checkEmail;
/*  Not a pure module */
