let renderForRoute = (route, router) =>
  ReactDOMRe.renderToElementWithId(<Body route router />, "root");

let router =
  DirectorRe.makeRouter({
    "/": "root",
    "/home": "home",
    "/register": "register",
    "/login": "login",
    "/settings": "settings",
    "/article/create": "article_create",
    "/article/edit": "article_edit",
    "/article": "article",
    "/profile": "profile",
  });

let handlers = {
  "root": () => renderForRoute(Routes.Home, router),
  "home": () => renderForRoute(Routes.Home, router),
  "register": () => renderForRoute(Routes.Register, router),
  "login": () => renderForRoute(Routes.Login, router),
  "settings": () => renderForRoute(Routes.Settings, router),
  "article_create": () => renderForRoute(Routes.CreateArticle, router),
  "article_edit": () => renderForRoute(Routes.EditArticle, router),
  "article": () => renderForRoute(Routes.Article, router),
  "profile": () => renderForRoute(Routes.Profile, router),
};

DirectorRe.configure(router, {"html5history": true, "resource": handlers});

DirectorRe.init(router, "/");
