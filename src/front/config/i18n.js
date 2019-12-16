/*
  ** i18n
  ** See https://github.com/nuxt-community/nuxt-i18n
  ** See https://github.com/nuxt-community/nuxt-i18n
  */

module.exports = {
  seo: false,
  defaultLocale: process.env.NUXT_MODULE_i18N_DEFAULT_LOCALE,
  lazy: true,
  langDir: 'lang/',
  locales: [
    {
      code: 'en',
      iso: 'en-US',
      file: 'en-US.js'
    },
    {
      code: 'pt',
      iso: 'pt-BR',
      file: 'pt-BR.js'
    }
  ]
}
