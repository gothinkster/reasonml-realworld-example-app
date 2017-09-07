let component = ReasonReact.statelessComponent "Body";
let show = ReasonReact.stringToElement;

/* Just like any other variant data can be carried around with variants with the routes */
let select_subpage route => {
  switch route {
    | Routes.Home => <Home router={route}/>
    | Routes.Login => <Login router={route} />
    | Routes.Register => <Register router={route} />
  };
};

let make ::route _children => { 
  ...component,
  render: fun _self => {
    <div>
      <Header router={route} /> 
      <div> (select_subpage route) </div>     
    </div>
  }  
};
