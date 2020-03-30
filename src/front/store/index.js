import Vuex from 'vuex'

import * as modules from './modules'

const createStore = () => {
  return new Vuex.Store({
    strict: process.env.NODE_ENV !== 'production',
    modules
  })
}

export default createStore
