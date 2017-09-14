var data = JSON.stringify({
  "user": {
    "email": "jake@jake.jake",
    "password": "jakejake"
  }
});

// var xhr = new XMLHttpRequest();
// xhr.withCredentials = true;

// xhr.addEventListener("readystatechange", function () {
//   if (this.readyState === 4) {
//     console.log(this.responseText);
//   }
// });

// xhr.open("POST", "https://conduit.productionready.io/api/users/login");
// xhr.setRequestHeader("content-type", "application/json");
// xhr.setRequestHeader("x-requested-with", "XMLHttpRequest");
// xhr.setRequestHeader("cache-control", "no-cache");

// xhr.send(data);
console.log(fetch);

fetch('https://conduit.productionready.io/api/tags', {
  method: 'GET',
  headers: {
    'Content-Type': 'application/json'
  }  
}).then(function(data){
  return data.json()
})
.then(function (result){
  console.log(result)
})
// .catch(function(error) {
//   console.log('request failed', error)
// });

let request = { 
  method: "POST", 
  headers: {"content-type": "application/json"}, 
  body: JSON.stringify({user: {email:"",password:""}}),     
}
// fetch("https://conduit.productionready.io/api/users", request)
//   .then(function(response){
//     return response.text()
//   })
//   .then(function(body){
//     console.log(body)
//   });

  
  console.log(request);
  var result = fetch("https://conduit.productionready.io/api/users", request)
    .then((function (prim) {
          return prim.text();
        }))
    .then(function(final){
      console.log("==================================================================")
      return Promise.resolve(console.log(final));
    })
  console.log(result);