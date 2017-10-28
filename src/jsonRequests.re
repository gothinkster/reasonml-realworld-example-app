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

let parseEmptyDefaultError () => {
  {
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

type responseType =
  | Error Js.Json.t
  | User Js.Json.t;

let getUserGraph responseText => {
  let user = responseText
    |> Js.Json.parseExn
    |> Js.Json.decodeObject
    |> Js.Option.andThen ((fun prop => Js.Dict.get prop "user") [@bs]);

  switch user {
    | Some json => json
    | None => Js.Json.parseExn {j|{}|j}
  };
};

let checkForErrors responseText => 
  responseText
    |> Js.Json.parseExn
    |> Js.Json.decodeObject
    |> Js.Option.andThen ((fun prop => Js.Dict.get prop "errors") [@bs]);

let convertErrorsToList errorJson => {
  let decodedJson = Js.Json.decodeObject errorJson;
  switch decodedJson {
    | Some errorList => {
      let errorKeys = Js.Dict.keys errorList;
      let errorValues = Js.Dict.values errorList;
       
      Array.mapi (fun acc errorField => {
        let validationError = Array.get errorValues acc;
        let frontCaps = String.capitalize errorField;
        {j|$frontCaps $validationError|j}
      }) errorKeys |> Array.to_list;
    }
    | None => []
  };
};

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
    |> then_ (fun response =>  actionFunc (Response.status response) (Response.text response) |> resolve);
  }
};

let authenticateUser loginFunc jsonData => sendRequest jsonData loginFunc Config.Authenticate;