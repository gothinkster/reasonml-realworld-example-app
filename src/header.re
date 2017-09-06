let component = ReasonReact.statelessComponent "Greeting";
let show = ReasonReact.stringToElement;

let make ::name _children => {
  ...component, /* spread the template's other defaults into here  */
  render: fun _self => <div> (show name) </div>
};