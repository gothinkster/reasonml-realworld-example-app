let component = ReasonReact.statelessComponent "Login";

let make _children => {
  ...component,
  render: fun _self => {
    <div />
  }
};