let component = ReasonReact.statelessComponent "Register";
let show = ReasonReact.stringToElement;

let make _children => {
  ...component,
  render: fun _self => {
    <div>(show "registration")</div>
  }
};