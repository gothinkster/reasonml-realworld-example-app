const path = require('path')

module.exports = {
  entry: {
    app: './lib/js/src/app.js'
  },
  devtool: 'source-map',
  output: {
    path: path.join(__dirname, '/public/'),
    filename: '[name].js'
  }
}