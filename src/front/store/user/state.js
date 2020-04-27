export default function state () {
  return {
    user: {},
    recaptcha: {
      size: 'invisible',
      challenged: false,
      success: false,
      siteKeyV3: process.env.NUXT_RECAPTCHA_SITE_KEY_V3,
      siteKeyV2: process.env.NUXT_RECAPTCHA_SITE_KEY_V2
    },
    auth: {
      token: '',
      refreshToken: ''
    },
    status: 'success'
  }
}
