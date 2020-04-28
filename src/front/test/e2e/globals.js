module.exports = {
  auth: {
    username: process.env.NUXT_NW_E2E_USER,
    password: process.env.NUXT_NW_E2E_PASS
  },
  before (done) {
    require('dotenv').config()
    done()
  }
}
