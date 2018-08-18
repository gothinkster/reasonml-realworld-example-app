open Infix;

let show = ReasonReact.string;

type state = {
  image: string,
  name: string,
  bio: string,
  email: string,
  password: string,
};

type action =
  | UpdateEmail(string)
  | UpdatePassword(string)
  | UpdateBio(string)
  | UpdateImage(string)
  | UpdateName(string)
  | SettingsFetched(state)
  | SettingsUpdated;

module Encode = {
  let userSettings = (settings: state) =>
    Json.Encode.(
      object_([
        ("email", string(settings.email)),
        ("password", string(settings.password)),
        ("image", string(settings.image)),
        ("username", string(settings.name)),
        ("bio", string(settings.bio)),
      ])
    );
  let user = (settings: state) =>
    Json.Encode.(object_([("user", userSettings(settings))]));
  let token = currentUser => Json.Encode.[("token", string(currentUser))];
};

let updateSettings = (router, event, {ReasonReact.state}) => {
  ReactEvent.Mouse.preventDefault(event);
  let responseCatch = (_status, payload) => {
    DirectorRe.setRoute(router, "/profile");
    payload
    |> Js.Promise.then_(result => {
         Js.log(result);
         result |> Js.Promise.resolve;
       })
    |> ignore;
  };
  JsonRequests.updateUser(
    responseCatch,
    Encode.user(state),
    Effects.getTokenFromStorage(),
  )
  |> ignore;
};

let updateImage = event => UpdateImage(ReactEvent.Form.target(event)##value);

let updateName = event => UpdateName(ReactEvent.Form.target(event)##value);

let updateBio = event => UpdateBio(ReactEvent.Form.target(event)##value);

let updateEmail = event => UpdateEmail(ReactEvent.Form.target(event)##value);

let updatePassword = event =>
  UpdatePassword(ReactEvent.Form.target(event)##value);

let getField =
  fun
  | Some(field) => field
  | None => "";

let component = ReasonReact.reducerComponent("Settings");

let make = (~router, _children) => {
  ...component,
  initialState: () => {image: "", name: "", bio: "", email: "", password: ""},
  reducer: (action, state) =>
    switch (action) {
    | UpdateEmail(email) => ReasonReact.Update({...state, email})
    | UpdatePassword(password) => ReasonReact.Update({...state, password})
    | UpdateBio(bio) => ReasonReact.Update({...state, bio})
    | UpdateImage(image) => ReasonReact.Update({...state, image})
    | UpdateName(name) => ReasonReact.Update({...state, name})
    | SettingsUpdated => ReasonReact.NoUpdate
    | SettingsFetched(updatedState) =>
      ReasonReact.Update({
        ...state,
        email: updatedState.email,
        name: updatedState.name,
        bio: updatedState.bio,
        image: updatedState.image,
      })
    },
  didMount: self => {
    let reduceCurrentUser = (_status, jsonPayload) =>
      jsonPayload
      |> Js.Promise.then_(result => {
           let parsedUser = JsonRequests.parseNewUser(result);
           self.send(
             SettingsFetched({
               image: getField(parsedUser.user.image),
               name: parsedUser.user.username,
               bio: getField(parsedUser.user.bio),
               email: parsedUser.user.email,
               password: "",
             }),
           );
           parsedUser.user |> Js.Promise.resolve;
         });
    let displayResult = result => {
      if (result == "401") {
        DirectorRe.setRoute(router, "/login");
      };
      let usersToken =
        JsonRequests.getUserGraph(result) |> JsonRequests.parseUser;
      JsonRequests.getCurrentUser(reduceCurrentUser, Some(usersToken.token))
      |> ignore;
      result |> Js.Promise.resolve;
    };
    let reduceUser = (_status, jsonPayload) =>
      jsonPayload |> Js.Promise.then_(displayResult);
    JsonRequests.getCurrentUser(reduceUser, Effects.getTokenFromStorage())
    |> ignore;
  },
  render: self =>
    <div className="settings-page">
      <div className="container page">
        <div className="row">
          <div className="col-md-6 offset-md-3 col-xs-12">
            <h1 className="text-xs-center"> {show("Your Settings")} </h1>
            <form>
              <fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control"
                    type_="text"
                    placeholder="URL of profile picture"
                    value={self.state.image}
                    onChange={updateImage >> self.send}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control form-control-lg"
                    type_="text"
                    placeholder="Your Name"
                    value={self.state.name}
                    onChange={updateName >> self.send}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <textarea
                    className="form-control form-control-lg"
                    rows=8
                    placeholder="Short bio about you"
                    value={self.state.bio}
                    onChange={updateBio >> self.send}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control form-control-lg"
                    type_="text"
                    placeholder="Email"
                    value={self.state.email}
                    onChange={updateEmail >> self.send}
                  />
                </fieldset>
                <fieldset className="form-group">
                  <input
                    className="form-control form-control-lg"
                    type_="password"
                    placeholder="Password"
                    value={self.state.password}
                    onChange={updatePassword >> self.send}
                  />
                </fieldset>
                <button
                  className="btn btn-lg btn-primary pull-xs-right"
                  onClick={self.handle(updateSettings(router))}>
                  {show("Update Settings")}
                </button>
              </fieldset>
            </form>
          </div>
        </div>
      </div>
    </div>,
};