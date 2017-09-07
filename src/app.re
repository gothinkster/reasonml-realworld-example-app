let renderForRoute route => {
  ReactDOMRe.renderToElementWithId <Body route /> "main-body";  
};

let router = 
  DirectorRe.makeRouter {
    "/": renderForRoute Routes.Home,
    "/register": renderForRoute Routes.Register,
    "/login": renderForRoute Routes.Login
  };

DirectorRe.configure router {"html5history": true};
DirectorRe.init router "/";