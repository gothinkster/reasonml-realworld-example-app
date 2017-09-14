open Bs_fetch;
open Config;

let make_headers (token: option string) => {
  let content_type = ("content-type", "application/json");
  switch token {
  | None => [|content_type|]
  | Some t => [|content_type, ("authorization", "Token " ^ t)|]
  }
};

let make_init method_ token (data: option Js.Json.t) => {
  let default_init =        
    RequestInit.make ::method_ headers::(HeadersInit.makeWithArray @@ make_headers token);

  switch data {
  | None => default_init ()
  | Some d => default_init body::(BodyInit.make @@ Js.Json.stringify d) ()
  }};

let toJson listedElements => {
  listedElements
  |> Js.Dict.fromList 
  |> Js.Json.object_;
};

let registerNewUser  registerFunc jsonData => {
  open Js.Promise;  

  let request = make_init Post None (Some jsonData); 
  fetchWithInit (apiUrlBase ^ (mapUrl Config.Authenticate)) request
  |> then_ (fun response => registerFunc (Response.status response) (Response.json response) |> resolve) |> ignore; 
};


