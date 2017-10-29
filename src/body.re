let component = ReasonReact.statelessComponent("Body");

let show = ReasonReact.stringToElement;

/* Just like any other variant data can be carried around with variants with the routes */
let make = (~route, ~router, _children) => {
  ...component,
  render: (_self) => {
    let select_subpage = (route) =>
      switch route {
      | Routes.Home => <Home />
      | Routes.Register => <Register router />
      | Routes.Login => <Login router />
      | Routes.Settings => <Settings />
      | Routes.Article => <Article />
      | Routes.CreateArticle => <CreateArticle />
      | Routes.EditArticle => <Article />
      };
    <div> <Header router /> <div> (route |> select_subpage) </div> <Footer /> </div>
  }
};
