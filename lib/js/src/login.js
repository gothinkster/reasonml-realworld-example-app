'use strict';

var Block       = require("bs-platform/lib/js/block.js");
var Curry       = require("bs-platform/lib/js/curry.js");
var React       = require("react");
var ReasonReact = require("reason-react/lib/js/src/reasonReact.js");

ReasonReact.statelessComponent("Login");

function show(prim) {
  return prim;
}

function goToRegister(router, $$event) {
  $$event.preventDefault();
  router.setRoute("/register");
  return /* () */0;
}

function login() {
  return /* Login */0;
}

function updateEmail($$event) {
  return /* EmailUpdate */Block.__(0, [$$event.target.value]);
}

function updatePassword($$event) {
  return /* PasswordUpdate */Block.__(1, [$$event.target.value]);
}

function loginUser(_, _$1, _$2) {
  console.log("log in the current user");
  return /* Login */0;
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
                                }, "Sign up"), React.createElement("p", {
                                  className: "text-xs-center"
                                }, React.createElement("a", {
                                      href: "#",
                                      onClick: (function (param) {
                                          return goToRegister(router, param);
                                        })
                                    }, "Need an account?")), React.createElement("form", undefined, React.createElement("fieldset", {
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
      } else if (action.tag) {
        return /* Update */Block.__(0, [/* record */[
                    /* email */state[/* email */0],
                    /* password */action[0],
                    /* hasValidationError */state[/* hasValidationError */2],
                    /* errorList */state[/* errorList */3]
                  ]]);
      } else {
        return /* Update */Block.__(0, [/* record */[
                    /* email */action[0],
                    /* password */state[/* password */1],
                    /* hasValidationError */state[/* hasValidationError */2],
                    /* errorList */state[/* errorList */3]
                  ]]);
      }
    });
  return newrecord;
}

exports.show           = show;
exports.goToRegister   = goToRegister;
exports.login          = login;
exports.updateEmail    = updateEmail;
exports.updatePassword = updatePassword;
exports.loginUser      = loginUser;
exports.component      = component;
exports.make           = make;
/*  Not a pure module */
