module.exports = {
  root: true,
  env: {
    browser: true,
    node: true
  },
  plugins: [
    'vue-a11y',
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
    'nuxt/no-cjs-in-config': 'off',
    'vue-a11y/click-events-have-key-events': 'off',
    'vue/max-attributes-per-line': 1,
    'import/order': 'off'
  }
}
