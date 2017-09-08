let component = ReasonReact.statelessComponent "Body";
let show = ReasonReact.stringToElement;

/* Just like any other variant data can be carried around with variants with the routes */
let select_subpage route => {
  switch route {
    | Routes.Home => "Home"
    | Routes.Register => "Register"
  };
};

let make ::route _children => { 
  ...component,
  render: fun _self => { 
    <div>
      <Header /> 
      <div> (show (select_subpage route)) </div>     
    </div>
  }  
};
