
import api from '@/services/api'
import * as MUTATIONS_TYPES from './mutation-types'
import { makeAuth } from './utils'

export default {
  setUser ({ commit }, user) {
    commit(MUTATIONS_TYPES.SET_USER, user)
    commit(MUTATIONS_TYPES.AUTH_STATUS_REQUEST, 'success')
  },

  logout ({ commit }) {
    commit(MUTATIONS_TYPES.LOGOUT)
  },

  login ({ commit }, user) {
    return new Promise((resolve, reject) => {
      commit(MUTATIONS_TYPES.AUTH_STATUS_REQUEST, 'loading')

      const formData = new FormData()
      formData.append('username', user.username)
      formData.append('password', user.password)
      formData.append('client_id', process.env.NUXT_AUTH_CLIENT_ID)
      formData.append('client_secret', process.env.NUXT_AUTH_CLIENT_SECRET)
      formData.append('grant_type', 'password')

      return makeAuth.call(this.app, commit, formData)
        .then(res => resolve(res))
        .catch(e => reject(e))
    })
  },

  refreshToken ({ state, commit }) {
    return new Promise((resolve, reject) => {
      commit(MUTATIONS_TYPES.AUTH_STATUS_REQUEST, 'loading')

      const formData = new FormData()
      formData.append('client_id', process.env.NUXT_AUTH_CLIENT_ID)
      formData.append('client_secret', process.env.NUXT_AUTH_CLIENT_SECRET)
      formData.append('refresh_token', state.auth.refreshToken)
      formData.append('grant_type', 'refresh_token')

      try {
        resolve(makeAuth.call(this.app, commit, formData))
      } catch (e) {
        reject(e)
      }
    })
  },

  checkScoreReCaptcha ({ commit }, response) {
    return new Promise((resolve, reject) => {
      return api({ path: `/recaptcha/verify/${response}` })
        .then((res) => {
          commit(MUTATIONS_TYPES.RECAPTCHA_SUCCESS)
          resolve(res)
        })
        .catch((e) => {
          commit(MUTATIONS_TYPES.RECAPTCHA_ERROR)
          reject(e)
        })
    })
  },

  reCaptchaSuccess ({ commit }) {
    commit(MUTATIONS_TYPES.RECAPTCHA_SUCCESS)
  },

  reCaptchaError ({ commit }) {
    commit(MUTATIONS_TYPES.RECAPTCHA_ERROR)
  }
}
