let component = ReasonReact.statelessComponent("Footer");

let show = ReasonReact.stringToElement;

let conduit_message = () =>
  <div>
    (show("An interactive learning project from "))
    <a href="https://thinkster.io"> (show("Thinkster")) </a>
    (show(". Code &amp; design licensed under MIT."))
  </div>;

let make = (_children) => {
  ...component,
  render: (_self) =>
    <footer>
      <div className="container">
        <a href="/" className="logo-font"> (show("conduit")) </a>
        <span className="attribution"> (conduit_message()) </span>
      </div>
    </footer>
};
