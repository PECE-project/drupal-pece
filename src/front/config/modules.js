module.exports = [
  // Doc: https://axios.nuxtjs.org/usage
  '@nuxtjs/axios',
  // Doc: https://github.com/nuxt-community/pwa-module
  ['@nuxtjs/pwa', { icon: false }],
  // Doc: https://github.com/nuxt-community/apollo-module
  '@nuxtjs/apollo',
  // Doc: https://github.com/nuxt-community/dotenv-module
  '@nuxtjs/dotenv',
  // Doc: https://github.com/nuxt-community/svg-sprite-module
  '@nuxtjs/svg-sprite',
  // Doc: https://github.com/nuxt-community/sitemap-module
  '@nuxtjs/sitemap',
  // Doc: https://github.com/nuxt-community/modules/tree/master/packages/browserconfig
  '@nuxtjs/browserconfig',
  // Doc: https://github.com/nuxt-community/webpackmonitor-module
  '@nuxtjs/webpackmonitor',
  // Doc: https://github.com/nuxt-community/style-resources-module#setup
  '@nuxtjs/style-resources',
  // Doc: https://nuxt-community.github.io/nuxt-i18n/
  'nuxt-i18n',
  // Doc: https://github.com/Developmint/nuxt-webfontloader
  'nuxt-webfontloader',
  // Doc: https://github.com/nuxt-community/recaptcha-module
  '@nuxtjs/recaptcha',
  // Doc: https://github.com/nuxt-community/modules/tree/master/packages/component-cache
  [
    '@nuxtjs/component-cache',
    {
      maxAge: 1000 * 60 * 60
    }
  ]
]
