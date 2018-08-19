let saveTokenToStorage = value =>
  Dom.Storage.(localStorage |> setItem("jwt", value));

let getTokenFromStorage = () => Dom.Storage.(localStorage |> getItem("jwt"));

let saveUserToStorage = (~bio=None, ~image=None, ~username) => {
  open Dom.Storage;
  localStorage |> setItem("username", username);
  switch (bio) {
  | Some(bio) => localStorage |> setItem("bio", bio)
  | None => ()
  };
  switch (image) {
  | Some(image) => localStorage |> setItem("image", image)
  | None => ()
  };
};

let getUserFromStorage = () => (
  Dom.Storage.(localStorage |> getItem("username")),
  Dom.Storage.(localStorage |> getItem("bio")),
  Dom.Storage.(localStorage |> getItem("image")),
);