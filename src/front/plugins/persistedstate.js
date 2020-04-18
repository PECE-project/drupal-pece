import SecureLS from 'secure-ls'
import createPersistedState from 'vuex-persistedstate'

const secureLsOptions = {
  encodingType: 'aes',
  isCompression: false,
  encryptionSecret: process.env.NUXT_AUTH_LS_ENCRYPTION_SECRET
}

const ls = new SecureLS(secureLsOptions)
ls.ls = {
  setItem: (key, value) => sessionStorage.setItem(key, value),
  getItem: key => sessionStorage.getItem(key),
  removeItem: key => sessionStorage.removeItem(key),
  get length () {
    return sessionStorage.length
  },
  key: i => sessionStorage.key(i),
  clear: () => sessionStorage.clear()
}

export default ({ store }) => {
  createPersistedState({
    key: 'user',
    paths: ['user.user'],
    storage: sessionStorage
  })(store)

  createPersistedState({
    key: 'auth',
    paths: ['user.auth'],
    storage: {
      getItem: key => ls.get(key),
      setItem: (key, value) => ls.set(key, value),
      removeItem: key => ls.remove(key)
    }
  })(store)
}
