require('dotenv').config()
const path = require('path')
const devServer = require(path.resolve(__dirname, 'config/devServer'))
const modules = require(path.resolve(__dirname, 'config/modules'))
const i18n = require(path.resolve(__dirname, 'config/i18n'))
const head = require(path.resolve(__dirname, 'config/head'))

module.exports = {
  /*
   ** Universal: Client-side and Server-side rendering
   */
  mode: 'universal',
  /*
   ** Headers of the page
   */
  head,
  /*
   ** Customize the progress-bar color
   */
  loading: { color: '#fff' },
  /*
   ** Global CSS
   */
  css: [],
  /*
   ** Plugins to load before mounting the App
   */
  plugins: [
    // Doc: https://github.com/vuejs/composition-api
    './plugins/composition-api',
    // Doc: https://github.com/vue-a11y/vue-announcer
    { src: './plugins/a11y/vue-announcer', mode: 'client' },
    // Doc: https://github.com/vue-a11y/vue-skip-to
    { src: './plugins/a11y/vue-skip-to', mode: 'client' },
    // Doc: https://github.com/vue-a11y/vue-axe
    { src: './plugins/a11y/vue-axe', mode: 'client' },
  ],
  /*
   ** Nuxt.js dev-modules
   */
  buildModules: [
    // Doc: https://github.com/nuxt-community/eslint-module
    '@nuxtjs/eslint-module',
    // Doc: https://github.com/nuxt-community/router-module
    [
      '@nuxtjs/router',
      {
        path: path.resolve(__dirname, 'router'),
        fileName: 'index.js'
      }
    ]
  ],
  /*
   ** Nuxt.js modules
   */
  modules,
  /*
   ** Axios module configuration
   ** See https://axios.nuxtjs.org/options
   */
  axios: {},
  /*
   ** Apollo module configuration
   ** See https://github.com/nuxt-community/apollo-module#setup
   */
  apollo: {
    clientConfigs: {
      default: {
        httpEndpoint: process.env.NUXT_MODULE_APOLLO_HTTP
      }
    }
  },
  /*
   ** Style configuration files
   */
  styleResources: {
    scss: [
      './assets/styles/library/settings/*.scss'
    ]
  },
  /*
   ** Sitemap module configuration
   ** See https://github.com/nuxt-community/sitemap-module#setup
   ** See https://github.com/ekalinin/sitemap.js#usage
   */
  sitemap: {
    hostname: '#',
    gzip: true
  },
  /*
   ** svg Sprite configuration
   */
  svgSprite: {
    input: '~/assets/svg/'
  },
  /*
   ** Browser config
   */
  browserconfig: {
    TileColor: '#6c6fd4'
  },
  /*
   ** Internacionalization
   */
  i18n,
  /*
   ** Build configuration
   */
  server: devServer.server,
  watchers: devServer.watchers,
  buildDir: path.resolve(__dirname, 'dist'),
  build: {
    extend (config, ctx) {}
  }
}
