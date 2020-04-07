import createPersistedState from 'vuex-persistedstate'

export default ({ store }) => {
  createPersistedState({
    key: 'user',
    paths: ['user'],
    storage: sessionStorage
  })(store)
}
