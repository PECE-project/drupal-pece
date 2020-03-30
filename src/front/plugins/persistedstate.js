import createPersistedState from 'vuex-persistedstate'

export default ({ store, isHMR, isClient }) => {
  if (isHMR) { return }

  if (isClient) {
    window.onNuxtReady((nuxt) => {
      createPersistedState()(store)
    })
  }
}
