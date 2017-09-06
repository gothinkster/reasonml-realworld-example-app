const express = require('express')
const app = express()
const path = require('path')

app.use(express.static('public'))
app.use('/js',express.static(path.join(__dirname, '/lib/js')))

app.listen(3000, () => {
  console.log('Server started on port: 3000')
})