open Config;
open Models;

let make_headers = (token: option(string)) => {
  let content_type = ("content-type", "application/json");
  switch token {
  | None => [|content_type|]
  | Some(t) => [|content_type, ("authorization", "Token " ++ t)|]
  }
};

let makeInit = (method, token, data: option(Js.Json.t)) => {
  let defaultInit =
    Bs_fetch.RequestInit.make(
      ~method_=method,
      ~headers=Bs_fetch.HeadersInit.makeWithArray @@ make_headers(token)
    );
  switch data {
  | None => defaultInit()
  | Some(d) => defaultInit(~body=Bs_fetch.BodyInit.make @@ Js.Json.stringify(d), ())
  }
};

let toJson = (listedElements) => listedElements |> Js.Dict.fromList |> Js.Json.object_;

type newUserResponse =
  | Succeed(user)
  | Failed(user);

let parseUser = (json) =>
  Json.Decode.{
    id: json |> field("id", int),
    email: json |> field("email", string),
    createdAt: json |> field("createdAt", string),
    updatedAt: json |> field("updatedAt", string),
    username: json |> field("username", string),
    bio: json |> optional(field("bio",string)),
    image: json |> optional(field("image",string)),
    token: json |> field("token", string)
  };

let parseNormalResp = (json) => {
  user: Json.Decode.(json |> field("user", parseUser)),
  errors: None
};

let parseErrors = (json) =>
  Some(
    Json.Decode.{
      email: json |> optional(field("email", array(string))),
      password: json |> optional(field("password", array(string))),
      username: json |> optional(field("username", array(string)))
    }
  );

let parseEmptyDefaultError = () => {
  id: 0,
  email: "",
  createdAt: "",
  updatedAt: "",
  username: "",
  bio: None,
  image: None,
  token: ""
};

let parseErrorResp = (errors) => {user: parseEmptyDefaultError(), errors};

let hasErrors = (checkId) =>
  switch checkId {
  | Some(_resp) => true
  | None => false
  };

let tee = (func, output) => {
  func(output);
  output
};

let parseNewUser = (responseText) => {
  let json = Js.Json.parseExn(responseText);
  let possibleErrors = Json.Decode.(json |> optional(field("errors", parseErrors)));
  switch possibleErrors {
  | Some(errors) => parseErrorResp(errors)
  | None => parseNormalResp(json)
  }
};

type responseType =
  | Error(Js.Json.t)
  | User(Js.Json.t);

let getUserGraph = (responseText) => {
  let user =
    responseText
    |> Js.Json.parseExn
    |> Js.Json.decodeObject
    |> Js.Option.andThen([@bs] ((prop) => Js.Dict.get(prop, "user")));
  switch user {
  | Some(json) => json
  | None => Js.Json.parseExn({j|{}|j})
  }
};

let checkForErrors = (responseText) =>
  responseText
  |> Js.Json.parseExn
  |> Js.Json.decodeObject
  |> Js.Option.andThen([@bs] ((prop) => Js.Dict.get(prop, "errors")));

let convertErrorsToList = (errorJson) => {
  let decodedJson = Js.Json.decodeObject(errorJson);
  switch decodedJson {
  | Some(errorList) =>
    let errorKeys = Js.Dict.keys(errorList);
    let errorValues = Js.Dict.values(errorList);
    Array.mapi(
      (acc, errorField) => {
        let validationError = errorValues[acc];
        let frontCaps = String.capitalize(errorField);
        {j|$frontCaps $validationError|j}
      },
      errorKeys
    )
    |> Array.to_list
  | None => []
  }
};

let registerNewUser = (registerFunc, jsonData) => {
  open Js.Promise;
  let request = makeInit(Post, None, Some(jsonData));
  Bs_fetch.(
    fetchWithInit(apiUrlBase ++ mapUrl(Config.Register), request)
    |> then_(
         (response) => registerFunc(Response.status(response), Response.text(response)) |> resolve
       )
  )
};

let constructUrl = (url) => apiUrlBase ++ mapUrl(url); 

let sendRequest = (requestMethod, token, jsonData, actionFunc, url) => {
  open Js.Promise;
  let request = makeInit(requestMethod, token, jsonData);
  Bs_fetch.(
    fetchWithInit(url, request)
    |> then_(
         (response) => actionFunc(Response.status(response), Response.text(response)) |> resolve
       )
  )
};

let authenticateUser = (loginFunc, jsonData) =>
  sendRequest(Post, None, Some(jsonData), loginFunc, constructUrl(Config.Authenticate));

let updateUser = (updateUserFunc, jsonData, token) => 
  sendRequest(Put, token, Some(jsonData), updateUserFunc, constructUrl(Config.UpdateUser));

let getCurrentUser = (getUserFunc, token) => 
  sendRequest(Get, token, None, getUserFunc, constructUrl(Config.CurrentUser));

let getMyArticles = (getArticleFunc, name, token) => {
  let urlAfterBase = apiUrlBase ++ mapUrl(Config.Articles) ++ "?author=" ++ name;
  sendRequest(Get, token, None, getArticleFunc, urlAfterBase); 
};

let getFavoritedArticles = (articleFunc, name, token) => {
  let urlAfterBase = apiUrlBase ++ mapUrl(Config.Articles) ++ "?favorited=" ++ name;
  sendRequest(Get, token, None, articleFunc, urlAfterBase); 
};

let getArticlesByTag = (articleFunc, tagName, token) => {
  let urlAfterBase = apiUrlBase ++ mapUrl(Config.Articles) ++ "?tag=" ++ tagName;
  sendRequest(Get, token, None, articleFunc, urlAfterBase); 
};

let getGlobalArticles = (getArticlesFunc, token, limit, offset) => {
  let urlAfterBase = apiUrlBase ++ mapUrl(Config.Articles) ++ "?limit=" ++ string_of_int(limit) ++ "&offset=" ++ string_of_int(offset);  
  sendRequest(Get, token, None, getArticlesFunc, urlAfterBase);
};

let getPoplarTags = (getTagsFunc) => {
  sendRequest(Get, None, None, getTagsFunc, constructUrl(Config.Tags));
};

let submitNewArticle = (submissionResponse, jsonData, token) => {
  sendRequest(Post, token, Some(jsonData), submissionResponse, (constructUrl(Config.Articles)))
};

let commentsForArticle = (slug, commentsFunc) => {
  sendRequest(Get, None, None, commentsFunc, (constructUrl(Config.ArticleCommentBySlug(slug))))
};

let mutedResponse = (_,_) => ();

let deleteCommentForArticle = (slug, commentId, token) => {
  sendRequest(Delete, token, None, mutedResponse, (constructUrl(Config.DeleteComment(slug, commentId))))
};

let followUser = (username, token) => {
  /* Using a muted response even though it returns a profile. It might be needed later */
  sendRequest(Post, token, None, mutedResponse, (constructUrl(Config.Follow(username))))
};

let unFollowUser = (username, token) => {
  sendRequest(Delete, token, None, mutedResponse, (constructUrl(Config.Unfollow(username))))
};

let getFeed = (token, articleListFunc) => {
  sendRequest(Get, token, None, articleListFunc, (constructUrl(Config.Feed)))
};

let favoriteArticle = (token, slug) => {
  sendRequest(Post, token, None, mutedResponse, (constructUrl(Config.ArticleFavorite(slug))))
};

let unfavoriteArticle = (token, slug) => {
  sendRequest(Delete, token, None, mutedResponse, (constructUrl(Config.ArticleFavorite(slug))))
}