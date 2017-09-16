let renderForRoute route router => ReactDOMRe.renderToElementWithId <Body route={route} router={router} /> "root";

let router =
  DirectorRe.makeRouter {
    "/": "root",
    "/home": "home",
    "/register": "register",
    "/login": "login",
    "/settings": "settings",
    "/article/create": "article_create",
    "/article/edit": "article_edit",
    "/article": "article"
  };

let handlers = {
  "root": fun () => renderForRoute Routes.Home router,
  "home": fun () => renderForRoute Routes.Home router,
  "register": fun () => renderForRoute Routes.Register router,
  "login": fun () => renderForRoute Routes.Login router,
  "settings": fun () => renderForRoute Routes.Settings router,
  "article_create": fun () => renderForRoute Routes.CreateArticle router,
  "article_edit": fun () => renderForRoute Routes.EditArticle router,
  "article": fun () => renderForRoute Routes.Article router
};

DirectorRe.configure router {
  "html5history": true,
  "resource": handlers
};

DirectorRe.init router "/";