open Models;

let defaultAuthor = {username: "", bio: None, image: None, following: false};

let defaultArticle = {
  slug: "",
  title: "",
  description: "",
  body: "",
  tagList: [||],
  createdAt: "",
  updatedAt: "",
  favorited: false,
  favoritesCount: 0,
  author: defaultAuthor,
};

type state = {currentArticle: article};

type action =
  | SetCurrentArticle(article);

let articleCallback = (send, currentArticle) =>
  send(SetCurrentArticle(currentArticle));

let component = ReasonReact.reducerComponent("Body");

/* Just like any other variant data can be carried around with variants with the routes */
let make = (~route, _children) => {
  ...component,
  initialState: () => {currentArticle: defaultArticle},
  reducer: (action, _state) =>
    switch (action) {
    | SetCurrentArticle(article) =>
      ReasonReact.Update({currentArticle: article})
    },
  render: self => {
    let {ReasonReact.state, send} = self;
    let article = state.currentArticle;
    let select_subpage = route =>
      switch (route) {
      | Routes.Home => <Home articleCallback={articleCallback(send)} />
      | Routes.Register => <Register />
      | Routes.Login => <Login />
      | Routes.Settings => <Settings />
      | Routes.Article => <Article article />
      | Routes.CreateArticle => <CreateArticle />
      | Routes.EditArticle => <Article article />
      | Routes.Profile => <Profile articleCallback={articleCallback(send)} />
      };
    <div> <Header /> <div> {route |> select_subpage} </div> <Footer /> </div>;
  },
};