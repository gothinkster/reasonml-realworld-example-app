let component = ReasonReact.statelessComponent "Home";

let make _children => {
  ...component,
  render: fun _self => {
    <div> (ReasonReact.stringToElement "this the home view") </div>
  }
};