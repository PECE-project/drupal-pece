import Vue from 'vue'

const requireComponent = require.context('.', false, /[\w-]+\.vue$/)

requireComponent.keys().forEach((fileName) => {
  const componentConfig = requireComponent(fileName)
  const componentName = fileName.replace(/^\.\//g, '').replace(/\.\w+$/, '')
  Vue.component(`Base${componentName}`, componentConfig.default || componentConfig)
})
