let component = ReasonReact.statelessComponent "Body";
let show = ReasonReact.stringToElement;

let make _children => {
  ...component,
  render: fun _self => {
    <div>
      <Header />
    </div>
  }
};