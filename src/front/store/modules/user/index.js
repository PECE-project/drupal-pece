import actions from './actions'
import mutations from './mutations'

const state = {
  user: {},
  token: '',
  refreshToken: '',
  status: 'success'
}

const getters = {
  user: state => state.user,
  getToken: state => state.token,
  authStatus: state => state.status,
  refreshToken: state => state.refreshToken
}

export default {
  namespaced: true,
  state,
  getters,
  mutations,
  actions
}
