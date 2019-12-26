const path = require('path')

const server = {
  host: process.env.NUXT_HOST || '0.0.0.0',
  port: process.env.NUXT_PORT || 5000,
  disableHostCheck: true,
  overlay: {
    warnings: true,
    errors: true
  }
}

let watchers = {
  webpack: {
    aggregateTimeout: 300,
    ignored: [
      path.resolve(__dirname, '../node_modules'),
      path.resolve(__dirname, '../dist'),
      path.resolve(__dirname, '../coverage'),
      path.resolve(__dirname, '../test'),
      path.resolve(__dirname, '../docker')
    ],
    poll: 1000
  }
}

if (process.env.DOCKER_DEV === 'false') {
  watchers = {}
}

module.exports = {
  server,
  watchers
}
