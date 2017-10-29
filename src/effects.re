let saveTokenToStorage = (value) => {
  Dom.Storage.(localStorage |> setItem("jwt", value))
};

let getTokenFromStorage = () => {
  Dom.Storage.(localStorage |> getItem("jwt"))
};