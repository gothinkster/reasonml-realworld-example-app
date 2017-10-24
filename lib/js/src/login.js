'use strict';

var List         = require("bs-platform/lib/js/list.js");
var $$Array      = require("bs-platform/lib/js/array.js");
var Block        = require("bs-platform/lib/js/block.js");
var Curry        = require("bs-platform/lib/js/curry.js");
var React        = require("react");
var Pervasives   = require("bs-platform/lib/js/pervasives.js");
var Json_encode  = require("bs-json/lib/js/src/json_encode.js");
var ReasonReact  = require("reason-react/lib/js/src/reasonReact.js");
var JsonRequests = require("./jsonRequests.js");

function show(prim) {
  return prim;
}

function goToRegister(router, $$event) {
  $$event.preventDefault();
  router.setRoute("/register");
  return /* () */0;
}

function encodeUserCredentials(creds) {
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "email",
                creds[/* email */0]
              ],
              /* :: */[
                /* tuple */[
                  "password",
                  creds[/* password */1]
                ],
                /* [] */0
              ]
            ]);
}

function user(topLevelUser) {
  return Json_encode.object_(/* :: */[
              /* tuple */[
                "user",
                encodeUserCredentials(topLevelUser)
              ],
              /* [] */0
            ]);
}

var Encode = /* module */[
  /* encodeUserCredentials */encodeUserCredentials,
  /* user */user
];

function updateEmail($$event) {
  return /* EmailUpdate */Block.__(1, [$$event.target.value]);
}

function updatePassword($$event) {
  return /* PasswordUpdate */Block.__(2, [$$event.target.value]);
}

function errorDisplayList(state) {
  return List.mapi((function (acc, errorMessage) {
                return React.createElement("ul", {
                            key: Pervasives.string_of_int(acc),
                            className: "error-messages"
                          }, React.createElement("li", undefined, errorMessage));
              }), List.filter((function (errorMessage) {
                      return +(errorMessage.length > 0);
                    }))(state[/* errorList */3]));
}

function loginUser(route, param, $$event) {
  var state = param[/* state */4];
  var reduce = param[/* reduce */3];
  $$event.preventDefault();
  JsonRequests.authenticateUser((function (_, jsonPayload) {
          return jsonPayload.then((function (json) {
                        var newUser = JsonRequests.checkForErrors(json);
                        var updatedState = newUser ? /* record */[
                            /* email */state[/* email */0],
                            /* password */state[/* password */1],
                            /* hasValidationError : true */1,
                            /* errorList */JsonRequests.convertErrorsToList(newUser[0])
                          ] : (route.setRoute("/home"), /* record */[
                              /* email */state[/* email */0],
                              /* password */state[/* password */1],
                              /* hasValidationError : false */0,
                              /* errorList */state[/* errorList */3]
                            ]);
                        return Promise.resolve(Curry._1(reduce, (function () {
                                          return /* Login */Block.__(0, [/* tuple */[
                                                      updatedState[/* hasValidationError */2],
                                                      updatedState[/* errorList */3]
                                                    ]]);
                                        })));
                      }));
        }), user(state));
  return /* LoginPending */0;
}

var component = ReasonReact.reducerComponent("Login");

function make(router, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (self) {
      var state = self[/* state */4];
      var reduce = self[/* reduce */3];
      return React.createElement("div", {
                  className: "auth-page"
                }, React.createElement("div", {
                      className: "container page"
                    }, React.createElement("div", {
                          className: "row"
                        }, React.createElement("div", {
                              className: "col-md-6 offset-md-3 col-xs-12"
                            }, React.createElement("h1", {
                                  className: "text-xs-center"
                                }, "Sign in"), React.createElement("p", {
                                  className: "text-xs-center"
                                }, React.createElement("a", {
                                      href: "#",
                                      onClick: (function (param) {
                                          return goToRegister(router, param);
                                        })
                                    }, "Need an account?")), state[/* hasValidationError */2] ? $$Array.of_list(errorDisplayList(state)) : null, React.createElement("form", undefined, React.createElement("fieldset", {
                                      className: "form-group"
                                    }, React.createElement("input", {
                                          className: "form-control form-control-lg",
                                          placeholder: "Email",
                                          type: "text",
                                          value: state[/* email */0],
                                          onChange: Curry._1(reduce, updateEmail)
                                        })), React.createElement("fieldset", {
                                      className: "form-group"
                                    }, React.createElement("input", {
                                          className: "form-control form-control-lg",
                                          placeholder: "Password",
                                          type: "password",
                                          value: state[/* password */1],
                                          onChange: Curry._1(reduce, updatePassword)
                                        })), React.createElement("button", {
                                      className: "btn btn-lg btn-primary pull-xs-right",
                                      onClick: Curry._1(reduce, (function (param) {
                                              return loginUser(router, self, param);
                                            }))
                                    }, "Sign in"))))));
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[
              /* email */"",
              /* password */"",
              /* hasValidationError : false */0,
              /* errorList : [] */0
            ];
    });
  newrecord[/* reducer */12] = (function (action, state) {
      if (typeof action === "number") {
        return /* NoUpdate */0;
      } else {
        switch (action.tag | 0) {
          case 0 : 
              var match = action[0];
              return /* Update */Block.__(0, [/* record */[
                          /* email */state[/* email */0],
                          /* password */state[/* password */1],
                          /* hasValidationError */match[0],
                          /* errorList */match[1]
                        ]]);
          case 1 : 
              return /* Update */Block.__(0, [/* record */[
                          /* email */action[0],
                          /* password */state[/* password */1],
                          /* hasValidationError */state[/* hasValidationError */2],
                          /* errorList */state[/* errorList */3]
                        ]]);
          case 2 : 
              return /* Update */Block.__(0, [/* record */[
                          /* email */state[/* email */0],
                          /* password */action[0],
                          /* hasValidationError */state[/* hasValidationError */2],
                          /* errorList */state[/* errorList */3]
                        ]]);
          
        }
      }
    });
  return newrecord;
}

exports.show             = show;
exports.goToRegister     = goToRegister;
exports.Encode           = Encode;
exports.updateEmail      = updateEmail;
exports.updatePassword   = updatePassword;
exports.errorDisplayList = errorDisplayList;
exports.loginUser        = loginUser;
exports.component        = component;
exports.make             = make;
/* component Not a pure module */
