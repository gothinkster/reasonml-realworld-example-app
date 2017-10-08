open Bs_fetch;
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
    RequestInit.make ::method_ headers::(HeadersInit.makeWithArray @@ make_headers token);

  switch data {
  | None => defaultInit ()
  | Some d => defaultInit body::(BodyInit.make @@ Js.Json.stringify d) ()
  }};

let toJson listedElements => {
  listedElements
  |> Js.Dict.fromList 
  |> Js.Json.object_;
};

type newUserResponse = 
  | Succeed user
  | Failed error_response;

let parseNormalResp json => {  
  Succeed Json.Decode.{
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

let parseErrors json => {
  Json.Decode.{
    email: json |> optional (field "email" (array string)),
    password: json |> optional (field "password" (array string)),
    username: json |> optional (field "username" (array string))
  };
};

let parseErrorResp json => {
  Failed Json.Decode.{
    errors: json |> field "errors" parseErrors
  };
}; 

let hasErrors (checkId: option newUserResponse) => {  
  switch checkId {
    | Some _resp => true
    | None => false
  };
};

let parseRegisteredUser _responseText => {
  ()
};

let parseNewUser responseText => {
  let json = Js.Json.parseExn responseText;

  let shouldDecodeAsResponse = 
    Json.Decode.(json |> optional (field "user" parseNormalResp))
    |> hasErrors;    
  
  shouldDecodeAsResponse ? (parseNormalResp json) : (parseErrorResp json);
};

let registerNewUser registerFunc jsonData => {
  open Js.Promise;  

  let request = makeInit Post None (Some jsonData); 
  fetchWithInit (apiUrlBase ^ (mapUrl Config.Register)) request
  |> then_ (fun response => registerFunc (Response.status response) (Response.text response) |> resolve); 
};