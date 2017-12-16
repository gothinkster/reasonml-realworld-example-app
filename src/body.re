open Models;
let show = ReasonReact.stringToElement;

let defaultAuthor = {
  username: "",
  bio: None,
  image: None,
  following: false
};

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
  author: defaultAuthor
};

type state = {
  currentArticle: article
};

type action =
  | SetCurrentArticle(article);

let articleCallback = (reduce, currentArticle) => {
  reduce((_) => SetCurrentArticle(currentArticle), ())
};

let component = ReasonReact.reducerComponent("Body");
/* Just like any other variant data can be carried around with variants with the routes */
let make = (~route, ~router, _children) => {
  ...component,
  initialState: () => { currentArticle: defaultArticle },
  reducer: (action, _state) =>
    switch action {
    | SetCurrentArticle(article) => ReasonReact.Update({currentArticle: article})
    },
  render: (self) => {
    let {ReasonReact.state, reduce} = self;
    let article = state.currentArticle;
    let select_subpage = (route) =>
      switch route {
      | Routes.Home => <Home articleCallback=articleCallback(reduce) router />
      | Routes.Register => <Register router />
      | Routes.Login => <Login router />
      | Routes.Settings => <Settings router />
      | Routes.Article => <Article router article />
      | Routes.CreateArticle => <CreateArticle router />
      | Routes.EditArticle => <Article router article />
      | Routes.Profile => <Profile articleCallback=articleCallback(reduce) router />
      };
    <div> <Header router /> <div> (route |> select_subpage) </div> <Footer /> </div>
  }
};
