module.exports = {
  auth: {
    username: 'ktquez@gmail.com',
    password: '01010101'
  },
  before (done) {
    require('dotenv').config()
    done()
  }
}
