module.exports = {
  '@tags': ['page'],
  'Login Test' (client) {
    client
      .login()
      .end()
  }
}
