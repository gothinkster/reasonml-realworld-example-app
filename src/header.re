let component = ReasonReact.statelessComponent "Header";
let show = ReasonReact.stringToElement;

let navigateTo router event routeName => {
  ReactEventRe.Mouse.preventDefault event;
  DirectorRe.setRoute router routeName;
};

let goToRegistration router event => {
  ReactEventRe.Mouse.preventDefault event;
  DirectorRe.setRoute router "/register";
};

let goToHome router routeName event => navigateTo router event routeName;

let make ::router _children => { 
  ...component, /* spread the template's other defaults into here  */
  render: fun _self => {    
    <div> 
      <nav className="navbar navbar-light">
        <div className="container">
          <a className="navbar-brand" href="index.html"> (show "conduit") </a>
          <ul className="nav navbar-nav pull-xs-right">
          <li className="nav-item">
            <a className="nav-link active" href="#/" onClick={goToHome router "/home"}> (show "Home") </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" href="#/article/create">
              <i className="ion-compose" /> (show " New Post") 
            </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" href="#/settings">
                <i className="ion-gear-a" /> (show " Settings") 
            </a>
          </li>
          <li className="nav-item">
            <a className="nav-link" href="#" onClick={goToRegistration router}> (show "Sign up") </a>
          </li>
        </ul>
        </div>
      </nav>
    </div>
  }
};