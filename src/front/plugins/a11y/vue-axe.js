import Vue from 'vue'

if (process.env.NODE_ENV === 'development') {
  const VueAxe = require('vue-axe')
  Vue.use(VueAxe, {
    config: {
      rules: [
        { id: 'heading-order', enabled: true },
        { id: 'label-title-only', enabled: true }
      ]
    }
  })
}
