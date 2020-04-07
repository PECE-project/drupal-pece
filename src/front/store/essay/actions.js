import * as MUTATIONS_TYPES from './mutation-types'

export default {
  setEssays ({ commit }, payload) {
    commit(MUTATIONS_TYPES.SET_ESSAYS, payload)
  }
}
