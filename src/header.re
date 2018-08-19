open Infix;

let component = ReasonReact.statelessComponent("Header");

let pointerStyle = () => ReactDOMRe.Style.make(~cursor="pointer", ());

let navigateTo = (event, routeName) => {
  ReactEvent.Mouse.preventDefault(event);
  ReasonReact.Router.push(routeName);
};

let goToRegistration = (routeName, event) => navigateTo(event, routeName);

let goToHome = (routeName, event) => navigateTo(event, routeName);

let goToSettings = (routeName, event) => navigateTo(event, routeName);

let goToCreateArticle = (routeName, event) => navigateTo(event, routeName);

let displayUsername = () => {
  let (optionalName, _, _) = Effects.getUserFromStorage();
  switch (optionalName) {
  | Some(name) => name
  | None => "Username Missing"
  };
};

/* This really should be in a reducer component since we are doing a side effect here. */
let displayByLogin = () =>
  switch (Effects.getTokenFromStorage()) {
  | Some(_token) =>
    <a
      className="nav-link"
      style={pointerStyle()}
      href="#"
      onClick={goToRegistration("/profile")}>
      {show(displayUsername())}
    </a>
  | None =>
    <a
      className="nav-link"
      style={pointerStyle()}
      href="#"
      onClick={goToRegistration("/register")}>
      {show("Sign up")}
    </a>
  };

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <nav className="navbar navbar-light">
        <div className="container">
          <a className="navbar-brand" href="index.html">
            {show("conduit")}
          </a>
          <ul className="nav navbar-nav pull-xs-right">
            <li className="nav-item">
              <a
                className="nav-link active"
                style={pointerStyle()}
                href="#"
                onClick={goToHome("/home")}>
                {show("Home")}
              </a>
            </li>
            <li className="nav-item">
              <a
                className="nav-link"
                style={pointerStyle()}
                href="#"
                onClick={goToCreateArticle("/article/create")}>
                <i className="ion-compose" />
                {show(" New Post")}
              </a>
            </li>
            <li className="nav-item">
              <a
                className="nav-link"
                style={pointerStyle()}
                href="#"
                onClick={goToSettings("/settings")}>
                <i className="ion-gear-a" />
                {show(" Settings")}
              </a>
            </li>
            <li className="nav-item"> {displayByLogin()} </li>
          </ul>
        </div>
      </nav>
    </div> /* spread the template's other defaults into here  */
};