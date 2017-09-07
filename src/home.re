let component = ReasonReact.statelessComponent "Home";

let make ::router _children => {
  ...component,
  render: fun _self => {
    <div />
  }
};