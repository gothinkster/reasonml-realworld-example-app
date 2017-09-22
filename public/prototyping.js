// var data = JSON.stringify({
//   "user": {
//     "email": "jake@jake.jake",
//     "password": "jakejake"
//   }
// });

// console.log(fetch);

// fetch('https://conduit.productionready.io/api/tags', {
//   method: 'GET',
//   headers: {
//     'Content-Type': 'application/json'
//   }
// }).then(function (data) {
//   return data.json()
// })
//   .then(function (result) {
//     console.log(result)
//   })

// let request = {
//   method: "POST",
//   headers: { "content-type": "application/json" },
//   body: JSON.stringify({ user: { email: "", password: "" } }),
// }

// console.log(request);
// var result = fetch("https://conduit.productionready.io/api/users", request)
//   .then((function (prim) {
//     return prim.text();
//   }))
//   .then(function (final) {
//     console.log("==================================================================")
//     return Promise.resolve(console.log(final));
//   })
// console.log(result);