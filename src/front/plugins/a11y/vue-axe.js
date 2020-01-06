import Vue from 'vue'

if (process.env.NODE_ENV === 'development') {
  const VueAxe = require('vue-axe')
  Vue.use(VueAxe, {
    clearConsoleOnUpdate: false,
    config: {}
  })
}
