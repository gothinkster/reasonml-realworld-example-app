type routes = 
  | Home
  | Register
  | Login;

let renderForRoute route => {
  ReactDOMRe.renderToElementWithId <Body route /> "main-body";  
};

let router = 
  DirectorRe.makeRouter {
    "/": renderForRoute Home,
    "/register": renderForRoute Register,
    "/login": renderForRoute Login
  };

DirectorRe.configure router {"html5history": true};
DirectorRe.init router "/";