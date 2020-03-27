import Vuex from 'vuex'
import createPersistedState from 'vuex-persistedstate'

import * as modules from './modules'

const createStore = () => {
  return new Vuex.Store({
    strict: process.env.NODE_ENV !== 'production',
    modules,
    plugins: [
      createPersistedState({
        key: 'user',
        paths: ['user'],
        storage: window.sessionStorage
      })
    ]
  })
}

export default createStore
