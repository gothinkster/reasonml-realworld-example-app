type user = {
  id: int,
  email: string,
  createdAt: string,
  updatedAt: string,
  username: string,
  bio: option string,
  image: option string,
  token: string
};

type errorDetails = {
  email: option (array string),
  password: option (array string),
  username: option (array string)
};

type newRegisteredUser = {
  errors: option errorDetails,
  user: option user,
};