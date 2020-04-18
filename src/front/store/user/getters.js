export default {
  user: state => state.user,
  getToken: state => state.auth.token,
  authStatus: state => state.status,
  refreshToken: state => state.auth.refreshToken
}
