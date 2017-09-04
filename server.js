const express = require('express')
const app = express()

app.use(express.static('public'))
app.listen(3000, function () {
  console.log('Server started on port: 3000')
})