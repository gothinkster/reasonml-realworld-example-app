'use strict';

var React       = require("react");
var ReasonReact = require("reason-react/lib/js/src/reasonReact.js");

var component = ReasonReact.statelessComponent("Header");

function show(prim) {
  return prim;
}

function navigateTo(router, $$event, routeName) {
  $$event.preventDefault();
  router.setRoute(routeName);
  return /* () */0;
}

function goToRegistration(router, $$event) {
  $$event.preventDefault();
  router.setRoute("/register");
  return /* () */0;
}

function goToHome(router, routeName, $$event) {
  return navigateTo(router, $$event, routeName);
}

function make(router, _) {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      return React.createElement("div", undefined, React.createElement("nav", {
                      className: "navbar navbar-light"
                    }, React.createElement("div", {
                          className: "container"
                        }, React.createElement("a", {
                              className: "navbar-brand",
                              href: "index.html"
                            }, "conduit"), React.createElement("ul", {
                              className: "nav navbar-nav pull-xs-right"
                            }, React.createElement("li", {
                                  className: "nav-item"
                                }, React.createElement("a", {
                                      className: "nav-link active",
                                      href: "#/",
                                      onClick: (function (param) {
                                          return navigateTo(router, param, "/home");
                                        })
                                    }, "Home")), React.createElement("li", {
                                  className: "nav-item"
                                }, React.createElement("a", {
                                      className: "nav-link",
                                      href: "#/article/create"
                                    }, React.createElement("i", {
                                          className: "ion-compose"
                                        }), " New Post")), React.createElement("li", {
                                  className: "nav-item"
                                }, React.createElement("a", {
                                      className: "nav-link",
                                      href: "#/settings"
                                    }, React.createElement("i", {
                                          className: "ion-gear-a"
                                        }), " Settings")), React.createElement("li", {
                                  className: "nav-item"
                                }, React.createElement("a", {
                                      className: "nav-link",
                                      href: "#",
                                      onClick: (function (param) {
                                          return goToRegistration(router, param);
                                        })
                                    }, "Sign up"))))));
    });
  return newrecord;
}

exports.component        = component;
exports.show             = show;
exports.navigateTo       = navigateTo;
exports.goToRegistration = goToRegistration;
exports.goToHome         = goToHome;
exports.make             = make;
/* component Not a pure module */
