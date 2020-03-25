module.exports = {
  root: true,
  env: {
    browser: true,
    node: true
  },
  plugins: [
    'vue-a11y',
    'eslint-plugin-import-helpers'
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
    'import-helpers/order-imports': [
      'warn',
      {
        newlinesBetween: 'always',
        groups: [
          '/^vue/',
          '/^@vue/',
          'module',
          '/^@\//',
          ['parent', 'sibling', 'index']
        ],
        alphabetize: { order: 'asc', ignoreCase: true }
      }
    ]
  }
}
