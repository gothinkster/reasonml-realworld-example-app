let show = ReasonReact.stringToElement;

type state = {
  image: string,
  name: string,
  bio: string,
  email: string,
  password: string
};

type action =
  | SettingsFetched(state)
  | SettingsUpdated;

module Encode = {
  let userSettings = (settings: state) => {
    Json.Encode.([
      ("email", string(settings.email)),
      ("password", string(settings.password)),
      ("image", string(settings.image)),
      ("username", string(settings.name)),
      ("bio", string(settings.bio))
    ]);
  };

  let token = (currentUser) => {
    Json.Encode.([
      ("token", string(currentUser))
    ]);
  };
};

let updateSettings = (event, {ReasonReact.state, reduce}) => {
  ReactEventRe.Mouse.preventDefault(event);
  Js.log("Should send request to server to update settings.");
};

let getField  =
  fun
  | Some(field) => field
  | None => "";

let component = ReasonReact.reducerComponent("Settings");
let make = (~router, _children) => {
  ...component,
  initialState: () => {image:"", name: "", bio: "", email: "", password:""},
  reducer: (action, state) =>
    switch action {
    | SettingsUpdated => ReasonReact.NoUpdate
    | SettingsFetched(updatedState) => ReasonReact.Update({
      ...state, 
      email: updatedState.email, 
      name: updatedState.name,
      bio: updatedState.bio,
      image: updatedState.image})
    },
  didMount: (self) => {
    let reduceCurrentUser = (_status, jsonPayload) => {
      jsonPayload |> Js.Promise.then_((result) => {
        let parsedUser = JsonRequests.parseNewUser(result);

        self.reduce((_) => SettingsFetched({
          image: getField(parsedUser.user.image),
          name: parsedUser.user.username,
          bio: getField(parsedUser.user.bio),
          email: parsedUser.user.email,
          password: "" }), ());
        parsedUser.user |> Js.Promise.resolve
      })
    };

    let displayResult = (result) => {
      if (result == "401"){
        DirectorRe.setRoute(router, "/login");
      };

      let usersToken = JsonRequests.getUserGraph(result) |> JsonRequests.parseUser;
      JsonRequests.getCurrentUser(reduceCurrentUser, Some(usersToken.token)) |> ignore;

      result |> Js.Promise.resolve
    };

    let reduceUser = (_status, jsonPayload) => jsonPayload |> Js.Promise.then_(displayResult);

    JsonRequests.getCurrentUser(reduceUser, Effects.getTokenFromStorage()) |> ignore;
    ReasonReact.NoUpdate
  },
  render: (self) =>
    <div className="settings-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> (show("Your Settings")) </h1>
            <form>
              <fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control"
                    _type="text"
                    placeholder="URL of profile picture"
                    value=(self.state.image)
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control form-control-lg"
                    _type="text"
                    placeholder="Your Name"
                    value=(self.state.name)
                  />
                </fieldset>
                <fieldset className="form-group">
                  <textarea
                    className="form-control form-control-lg"
                    rows=8
                    placeholder="Short bio about you"
                    value=(self.state.bio)
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control form-control-lg"
                    _type="text"
                    placeholder="Email"
                    value=(self.state.email)
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control form-control-lg"
                    _type="password"
                    placeholder="Password"
                    value=(self.state.password)
                  />
                </fieldset>
                <button className="btn btn-lg btn-primary pull-xs-right" onClick=(self.handle(updateSettings))>
                  (show("Update Settings"))
                </button>
              </fieldset>
            </form>
          </div>
        </div>
      </div>
    </div>
};
