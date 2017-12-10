let saveTokenToStorage = (value) => {
  Dom.Storage.(localStorage |> setItem("jwt", value))
};

let getTokenFromStorage = () => {
  Dom.Storage.(localStorage |> getItem("jwt"))
};

let saveUserToStorage = (username, bio, image) => {
  open Dom.Storage;
  localStorage |> setItem("username", username);
  localStorage |> setItem("image", image);
  
  switch bio {
    | Some(bio) => localStorage |> setItem("bio", bio)
    | None => ()
  };
};

let getUserFromStorage = () => {
  (Dom.Storage.(localStorage |> getItem("username")), 
   Dom.Storage.(localStorage |> getItem("bio")),
   Dom.Storage.(localStorage |> getItem("image")));
};