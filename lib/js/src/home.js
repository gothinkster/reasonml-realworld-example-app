'use strict';

var React       = require("react");
var ReasonReact = require("reason-react/lib/js/src/reasonReact.js");

var component = ReasonReact.statelessComponent("Home");

function show(prim) {
  return prim;
}

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      return React.createElement("div", {
                  className: "home-page"
                }, React.createElement("div", {
                      className: "banner"
                    }, React.createElement("div", {
                          className: "container"
                        }, React.createElement("h1", {
                              className: "logo-font"
                            }, "conduit"), React.createElement("p", undefined, "A place to share your knowledge."))), React.createElement("div", {
                      className: "container page"
                    }, React.createElement("div", {
                          className: "row"
                        }, React.createElement("div", {
                              className: "col-md-9"
                            }, React.createElement("div", {
                                  className: "feed-toggle"
                                }, React.createElement("ul", {
                                      className: "nav nav-pills outline-active"
                                    }, React.createElement("li", {
                                          className: "nav-item"
                                        }, React.createElement("a", {
                                              className: "nav-link disabled",
                                              href: ""
                                            }, "Your Feed")), React.createElement("li", {
                                          className: "nav-item"
                                        }, React.createElement("a", {
                                              className: "nav-link active",
                                              href: ""
                                            }, "Global Feed")))), React.createElement("div", {
                                  className: "article-preview"
                                }, React.createElement("div", {
                                      className: "article-meta"
                                    }, React.createElement("a", {
                                          href: "profile.html"
                                        }), React.createElement("div", {
                                          className: "info"
                                        }, React.createElement("a", {
                                              className: "author",
                                              href: ""
                                            }, "Eric Simons"), React.createElement("span", {
                                              className: "date"
                                            }, "January 20th")), React.createElement("button", {
                                          className: "btn btn-outline-primary btn-sm pull-xs-right"
                                        }, React.createElement("i", {
                                              className: "ion-heart"
                                            }), "29")), React.createElement("a", {
                                      className: "preview-link",
                                      href: ""
                                    }, React.createElement("h1", undefined, "How to build webapps that scale"), React.createElement("p", undefined, "This is the description for the post."), React.createElement("span", undefined, "Read more..."))), React.createElement("div", {
                                  className: "article-preview"
                                }, React.createElement("div", {
                                      className: "article-meta"
                                    }, React.createElement("a", {
                                          href: "profile.html"
                                        }), React.createElement("div", {
                                          className: "info"
                                        }, React.createElement("a", {
                                              className: "author",
                                              href: ""
                                            }, "Albert Pai"), React.createElement("span", {
                                              className: "date"
                                            }, "January 20th")), React.createElement("button", {
                                          className: "btn btn-outline-primary btn-sm pull-xs-right"
                                        }, React.createElement("i", {
                                              className: "ion-heart"
                                            }), "32")), React.createElement("a", {
                                      className: "preview-link",
                                      href: ""
                                    }, React.createElement("h1", undefined, "The song you won't ever stop singing. No matter how hard you try."), React.createElement("p", undefined, "This is the description for the post."), React.createElement("span", undefined, "Read more...")))), React.createElement("div", {
                              className: "col-md-3"
                            }, React.createElement("div", {
                                  className: "sidebar"
                                }, React.createElement("p", undefined, "Popular Tags"), React.createElement("div", {
                                      className: "tag-list"
                                    }, React.createElement("a", {
                                          className: "tag-pill tag-default",
                                          href: ""
                                        }, "programming"), React.createElement("a", {
                                          className: "tag-pill tag-default",
                                          href: ""
                                        }, "javascript"), React.createElement("a", {
                                          className: "tag-pill tag-default",
                                          href: ""
                                        }, "emberjs"), React.createElement("a", {
                                          className: "tag-pill tag-default",
                                          href: ""
                                        }, "angularjs"), React.createElement("a", {
                                          className: "tag-pill tag-default",
                                          href: ""
                                        }, "react"), React.createElement("a", {
                                          className: "tag-pill tag-default",
                                          href: ""
                                        }, "mean"), React.createElement("a", {
                                          className: "tag-pill tag-default",
                                          href: ""
                                        }, "node"), React.createElement("a", {
                                          className: "tag-pill tag-default",
                                          href: ""
                                        }, "rails")))))));
    });
  return newrecord;
}

var profile_image = "http://i.imgur.com/Qr71crq.jpg";

var second_image = "\"http://i.imgur.com/N4VcUeJ.jpg\"";

exports.component     = component;
exports.show          = show;
exports.profile_image = profile_image;
exports.second_image  = second_image;
exports.make          = make;
/* component Not a pure module */
