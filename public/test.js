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
}).then(function (result){
  console.log(result)
})
.catch(function(error) {
  console.log('request failed', error)
});