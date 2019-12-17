module.exports = {
  root: true,
  env: {
    browser: true,
    node: true
  },
  plugins: [
    'vue-a11y'
  ],
  parserOptions: {
    parser: 'babel-eslint'
  },
  extends: [
    '@nuxtjs',
    'plugin:nuxt/recommended',
    'plugin:vue-a11y/base'
  ],
  rules: {
    'no-console': 'off',
    'nuxt/no-cjs-in-config': 'off'
  }
}
