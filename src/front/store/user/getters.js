export default {
  user: state => state.user,
  getToken: state => state.auth.token,
  recaptcha: state => state.recaptcha,
  authStatus: state => state.status,
  refreshToken: state => state.auth.refreshToken
}
