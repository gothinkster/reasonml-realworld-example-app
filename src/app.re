let renderForRoute route => ReactDOMRe.renderToElementWithId <Body route={route} /> "root";

let router =
  DirectorRe.makeRouter {
    "/": fun () => renderForRoute Routes.Home,
    "/home": fun () => renderForRoute Routes.Home,
    "/register": fun () => renderForRoute Routes.Register,
    "/Login": fun () => renderForRoute Routes.Login,
    "/Settings": fun () => renderForRoute Routes.Settings
  };

DirectorRe.init router "/";