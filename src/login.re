let component = ReasonReact.statelessComponent "Login";

let make ::router _children => {
  ...component,
  render: fun _self => {
    <div />
  }
};