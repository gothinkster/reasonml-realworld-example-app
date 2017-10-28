let saveTokenToStorage = (value) => {
  Dom.Storage.(localStorage |> setItem("jwt", value))
};