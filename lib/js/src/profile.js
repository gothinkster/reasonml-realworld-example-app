'use strict';

var React       = require("react");
var ReasonReact = require("reason-react/lib/js/src/reasonReact.js");

var component = ReasonReact.statelessComponent("Profile");

function show(prim) {
  return prim;
}

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function () {
      return React.createElement("div", {
                  className: "profile-page"
                }, React.createElement("div", {
                      className: "user-info"
                    }, React.createElement("div", {
                          className: "container"
                        }, React.createElement("div", {
                              className: "row"
                            }, React.createElement("div", {
                                  className: "col-xs-12 col-md-10 offset-md-1"
                                }, React.createElement("img", {
                                      className: "user-img",
                                      src: "http://i.imgur.com/Qr71crq.jpg"
                                    }), React.createElement("h4", undefined, "Eric Simons"), React.createElement("p", undefined, "Cofounder @GoThinkster, lived in Aol's HQ for a few months, kinda looks like Peeta from the Hunger Games"), React.createElement("button", {
                                      className: "btn btn-sm btn-outline-secondary action-btn"
                                    }, React.createElement("i", {
                                          className: "ion-plus-round"
                                        }), "&nbsp;", "Follow Eric Simons"))))), React.createElement("div", {
                      className: "container"
                    }, React.createElement("div", {
                          className: "row"
                        }, React.createElement("div", {
                              className: "col-xs-12 col-md-10 offset-md-1"
                            }, React.createElement("div", {
                                  className: "articles-toggle"
                                }, React.createElement("ul", {
                                      className: "nav nav-pills outline-active"
                                    }, React.createElement("li", {
                                          className: "nav-item"
                                        }, React.createElement("a", {
                                              className: "nav-link active",
                                              href: ""
                                            }, "My Articles")), React.createElement("li", {
                                          className: "nav-item"
                                        }, React.createElement("a", {
                                              className: "nav-link",
                                              href: ""
                                            }, "Favorited Articles")))), React.createElement("div", {
                                  className: "article-preview"
                                }, React.createElement("div", {
                                      className: "article-meta"
                                    }, React.createElement("a", {
                                          href: "#/home"
                                        }, React.createElement("img", {
                                              src: "http://i.imgur.com/Qr71crq.jpg"
                                            })), React.createElement("div", {
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
                                          href: ""
                                        }, React.createElement("img", {
                                              src: "http://i.imgur.com/N4VcUeJ.jpg"
                                            })), React.createElement("div", {
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
                                    }, React.createElement("h1", undefined, "The song you won't ever stop singing. No matter how hard you try."), React.createElement("p", undefined, "This is the description for the post."), React.createElement("span", undefined, "Read more..."), React.createElement("ul", {
                                          className: "tag-list"
                                        }, React.createElement("li", {
                                              className: "tag-default tag-pill tag-outline"
                                            }, "Music"), React.createElement("li", {
                                              className: "tag-default tag-pill tag-outline"
                                            }, "Song"))))))));
    });
  return newrecord;
}

exports.component = component;
exports.show      = show;
exports.make      = make;
/* component Not a pure module */
