let saveTokenToStorage = (value) => {
  Dom.Storage.(localStorage |> setItem("jwt", value))
};

let getTokenFromStorage = () => {
  Dom.Storage.(localStorage |> getItem("jwt"))
};

let saveUserToStorage = (user) => {
  Dom.Storage.(localStorage |> setItem("currentUser", user))
};