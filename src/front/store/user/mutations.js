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
    state.auth.token = payload.token
    state.auth.refreshToken = payload.refreshToken
  },
  /**
   * Logout user
   *
   * @param {Object} state
   */
  [MUTATIONS_TYPES.LOGOUT] (state) {
    state.status = ''
    state.auth.token = ''
    state.auth.refreshToken = ''
    state.user = {}
    location.reload()
  },
  /**
   * reCaptcha Success score
   *
   * @param {Object} state
   */
  [MUTATIONS_TYPES.RECAPTCHA_SUCCESS] (state) {
    state.recaptcha.success = true
  },
  /**
   * reCaptcha Error score
   *
   * @param {Object} state
   */
  [MUTATIONS_TYPES.RECAPTCHA_ERROR] (state) {
    state.recaptcha.challenged = true
    state.recaptcha.size = 'normal'
  }
}
