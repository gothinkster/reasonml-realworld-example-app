let renderForRoute route => ReactDOMRe.renderToElementWithId <Body route={route} /> "root";

let router =
  DirectorRe.makeRouter {
    "/": fun () => renderForRoute Routes.Home,
    "/home": fun () => renderForRoute Routes.Home,
    "/register": fun () => renderForRoute Routes.Register,
    "/Login": fun () => renderForRoute Routes.Login,
    "/Settings": fun () => renderForRoute Routes.Settings,
    "/article/create": fun () => renderForRoute Routes.CreateArticle,
    "/article/edit": fun () => renderForRoute Routes.EditArticle,
    "/article": fun () => renderForRoute Routes.Article
  };

DirectorRe.init router "/";