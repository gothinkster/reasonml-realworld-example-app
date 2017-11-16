type user = {
  id: int,
  email: string,
  createdAt: string,
  updatedAt: string,
  username: string,
  bio: option(string),
  image: option(string),
  token: string
};

type errorDetails = {
  email: option(array(string)),
  password: option(array(string)),
  username: option(array(string))
};

type registeredUser = {
  errors: option(errorDetails),
  user
};

type articleDetails = {
  title: string,
  description: string,
  body: string,
  tags: array(string)
};

type newArticle = {
  article: articleDetails
};
