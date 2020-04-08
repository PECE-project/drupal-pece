const faker = require('faker')

function generateDataRegister () {
  return {
    username: faker.internet.userName(),
    email: faker.internet.email(),
    password: '01010101',
    zotero: faker.internet.email()
  }
}

module.exports = {
  generateDataRegister
}
