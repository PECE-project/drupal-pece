const faker = require('faker')

function generateDataRegister () {
  return {
    email: faker.internet.email(),
    password: '123456789',
    zotero: faker.internet.email()
  }
}

module.exports = {
  generateDataRegister
}
