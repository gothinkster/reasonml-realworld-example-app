let renderForRoute route => ReactDOMRe.renderToElementWithId <Body route={route} /> "root";

let router =
  DirectorRe.makeRouter {
    "/": fun () => renderForRoute Routes.Home,
    "/home": fun () => renderForRoute Routes.Home,
    "/register": fun () => renderForRoute Routes.Register,
    "/login": fun () => renderForRoute Routes.Login,
    "/settings": fun () => renderForRoute Routes.Settings,
    "/article/create": fun () => renderForRoute Routes.CreateArticle,
    "/article/edit": fun () => renderForRoute Routes.EditArticle,
    "/article": fun () => renderForRoute Routes.Article
  };

DirectorRe.init router "/";