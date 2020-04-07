import * as MUTATIONS_TYPES from './mutation-types'

export default {
  /**
   * Set essays in store
   *
   * @param {Object} state
   */
  [MUTATIONS_TYPES.SET_ESSAYS] (state, payload) {
    state.essays = [ state.essays, ...payload ]
  }
}
