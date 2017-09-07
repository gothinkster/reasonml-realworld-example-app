let component = ReasonReact.statelessComponent "Body";
let show = ReasonReact.stringToElement;

/* Just like any other variant data can be carried around with variants with the routes */

let make ::route _children => {
  ...component,
  render: fun _self => {
    <div>
      <Header />
      <div id="mid-page" />
    </div>
  }
};
