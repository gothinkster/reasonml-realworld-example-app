let component = ReasonReact.statelessComponent "Register";
let show = ReasonReact.stringToElement;

let make ::router _children => {
  ...component,
  render: fun _self => {
    <div>(show "registration")</div>
  }
};