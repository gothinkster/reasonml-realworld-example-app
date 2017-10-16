open Config;
open Models;

let make_headers (token: option string) => {
  let content_type = ("content-type", "application/json");
  switch token {
  | None => [|content_type|]
  | Some t => [|content_type, ("authorization", "Token " ^ t)|]
  }
};

let makeInit method_ token (data: option Js.Json.t) => {
  let defaultInit =
    Bs_fetch.RequestInit.make ::method_ headers::(Bs_fetch.HeadersInit.makeWithArray @@ make_headers token);

  switch data {
  | None => defaultInit ()
  | Some d => defaultInit body::(Bs_fetch.BodyInit.make @@ Js.Json.stringify d) ()
  }};

let toJson listedElements => {
  listedElements
  |> Js.Dict.fromList
  |> Js.Json.object_;
};

type newUserResponse =
  | Succeed user
  | Failed user;

let parseUser json => {
  Json.Decode.{
    id: json |> field "id" int,
    email: json |> field "email" string,
    createdAt: json |> field "createdAt" string,
    updatedAt: json |> field "updatedAt" string,
    username: json |> field "username" string,
    bio: None,
    image: None,
    token: json |> field "token" string
  };
};

let parseEmptyError _json => {
  Json.Decode.{
    email: None,
    password: None,
    username: None
  };
};

let parseEmptyDefaultError () => {
  Json.Decode.{
    id: 0,
    email: "",
    createdAt: "",
    updatedAt: "",
    username: "",
    bio: None,
    image: None,
    token: ""
  };
};

let parseNormalResp json => {
  { user: Json.Decode.(json |> field "user" parseUser),
    errors: None
  };
};

let parseErrors json => {
  Some Json.Decode.{
    email: json |> optional (field "email" (array string)),
    password: json |> optional (field "password" (array string)),
    username: json |> optional (field "username" (array string))
  };
};

let parseErrorResp errors => {
  {
    user: parseEmptyDefaultError (),
    errors: errors
  };
};

let hasErrors (checkId) => {
  switch checkId {
    | Some _resp => true
    | None => false
  };
};

let tee func output => {
  func (output);
  output
};

let parseNewUser responseText => {
  let json = Js.Json.parseExn responseText;

  let possibleErrors = Json.Decode.(json |> optional (field "errors" parseErrors));
  switch possibleErrors {
    | Some errors => parseErrorResp errors
    | None => parseNormalResp json
  };
};

let parseCurrentUser responseText => parseNewUser responseText; 

let registerNewUser registerFunc jsonData => {
  open Js.Promise;

  let request = makeInit Post None (Some jsonData);

  {
    open Bs_fetch;
    fetchWithInit (apiUrlBase ^ (mapUrl Config.Register)) request
    |> then_ (fun response => registerFunc (Response.status response) (Response.text response) |> resolve);
  }
};

let sendRequest jsonData actionFunc url => {
  open Js.Promise;
  
  let request = makeInit Post None (Some jsonData);

  {
    open Bs_fetch;
    fetchWithInit (apiUrlBase ^ (mapUrl url)) request
    |> then_ (fun response => actionFunc (Response.status response) (Response.text response) |> resolve);
  }
};

let authenticateUser loginFunc jsonData => sendRequest jsonData loginFunc Config.Authenticate;
