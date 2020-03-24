module.exports = [
  // Register base componentes
  '@/components/base/_globals',
  // Doc: https://github.com/vuejs/composition-api
  '@/plugins/composition-api',
  // Doc: https://github.com/logaretm/vee-validate
  '@/plugins/vee-validate',
  // Doc: https://github.com/maoberlehner/vue-lazy-hydration
  '@/plugins/lazy-hydration',
  // Doc: https://github.com/vue-a11y/vue-announcer
  { src: '@/plugins/a11y/vue-announcer', mode: 'client' },
  // Doc: https://github.com/vue-a11y/vue-skip-to
  { src: '@/plugins/a11y/vue-skip-to', mode: 'client' },
  // Doc: https://github.com/vue-a11y/vue-axe
  { src: '@/plugins/a11y/vue-axe', mode: 'client' }
]
