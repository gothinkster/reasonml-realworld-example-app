let apiUrlBase = "https://conduit.productionready.io/api";

type urlMap = 
  | Authenticate
  | Register
  | CurrentUser
  | UpdateUser
  | Profile string
  | Follow string
  | Unfollow string
  | Articles
  | ArticleBySlug string
  | ArticleCommentBySlug string
  | ArticleBySlugId (string, string)
  | ArticleFavorite string
  | ArticleUnfavorite string
  | Tags
  | Feed;
  
let mapUrl url => {
  switch url {
    | Authenticate => "/users/login"
    | Register => "/users"
    | CurrentUser | UpdateUser => "/user"
    | Profile username => "/profiles/" ^ username
    | Follow username | Unfollow username => "/profiles/" ^ username ^ "/follow"
    | Articles => "/articles"
    | ArticleBySlug slug => "/articles/" ^ slug
    | ArticleCommentBySlug slug => "/articles/" ^ slug ^ "/comments"
    | ArticleBySlugId (slug, id) => "/articles/" ^ slug ^ "/comments/" ^ id
    | Feed => "/articles/feed"
    | ArticleFavorite slug | ArticleUnfavorite slug => "/articles/" ^ slug ^ "/favorite"
    | Tags => "/tags"
  };
};

let getUrl endpoint => {};