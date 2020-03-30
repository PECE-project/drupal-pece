import * as MUTATIONS_TYPES from './mutation-types'

export default {
  /**
   * Set user in store
   *
   * @param {Object} state
   */
  [MUTATIONS_TYPES.SET_USER] (state, payload) {
    state.user = { ...payload }
  },
  /**
   * Set status of auth request
   *
   * @param {Object} state
   */
  [MUTATIONS_TYPES.AUTH_STATUS_REQUEST] (state, status) {
    state.status = status
  },
  /**
   * Set data of authentication
   *
   * @param {Object} state
   */
  [MUTATIONS_TYPES.AUTH_SUCCESS] (state, payload) {
    state.status = 'success'
    state.token = payload.token
    state.refreshToken = payload.refreshToken
  },
  /**
   * Logout user
   *
   * @param {Object} state
   */
  [MUTATIONS_TYPES.LOGOUT] (state) {
    state.status = ''
    state.token = ''
    state.refreshToken = ''
    state.user = {}
    location.reload()
  }
}
