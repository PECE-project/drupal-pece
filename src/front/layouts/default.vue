<template>
  <div id="pece-app">
    <TheHeaderAdmin />
    <div class="xl:px-6">
      <the-heading />
      <the-main>
        <nuxt />
      </the-main>
      <lazy-hydrate ssr-only>
        <the-footer class="my-8 sm:my-16" />
      </lazy-hydrate>
    </div>
  </div>
</template>

<script>
import TheHeading from '@/components/layout/TheHeading'
import TheMain from '@/components/layout/TheMain'

export default {
  components: {
    TheHeading,
    TheMain,
    TheFooter: () => import('@/components/layout/TheFooter'),
    TheHeaderAdmin: () => import(/* webpackChunkName: "TheHeaderAdmin" */ '@/components/layout/TheHeaderAdmin')
  },
  head () {
    return { ...this.$nuxtI18nSeo() }
  }
}
</script>

<style src="~/assets/styles/main.scss" lang="scss"></style>
