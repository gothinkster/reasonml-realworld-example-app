open Routes;

type state = {
  active: routes,
  isLoggedIn: bool,
};

let component = ReasonReact.reducerComponent("AppRoot");

let make = _children => {
  ...component,
  initialState: () => {active: Home, isLoggedIn: true},
  reducer: (action, state: state) =>
    switch (action) {
    /* router actions */
    | _ as active => ReasonReact.Update({...state, active})
    },
  didMount: ({state, send, onUnmount}) => {
    let watcherID =
      ReasonReact.Router.watchUrl(url =>
        switch (url.path, state.isLoggedIn) {
        | (["/"] | ["/home"], _) => send(Home)
        | (["register"], _) => send(Register)
        | (["login"], _) => send(Login)
        | (["article", "create"], _) => send(CreateArticle)
        | (["article", "edit"], _) => send(EditArticle)
        | (["article"], _) => send(Article)
        | (["profile"], _) => send(Profile)
        | (["settings"], _) => send(Settings)
        | _ => send(Home)
        }
      );
    onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  render: self => <Body route={self.state.active} />,
};