module.exports = {
  auth: {
    email: process.env.NUXT_NW_E2E_EMAIL,
    password: process.env.NUXT_NW_E2E_PASS
  },
  before (done) {
    require('dotenv').config()
    done()
  }
}
