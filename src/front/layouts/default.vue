<template>
  <div>
    <the-heading />
    <the-main>
      <nuxt />
    </the-main>
    <lazy-hydrate ssr-only>
      <the-footer />
    </lazy-hydrate>
  </div>
</template>

<script>
import TheHeading from '@/components/layout/TheHeading'
import TheMain from '@/components/layout/TheMain'

export default {
  components: {
    TheHeading,
    TheMain,
    TheFooter: () => import('@/components/layout/TheFooter')
  },
  head () {
    return { ...this.$nuxtI18nSeo() }
  }
}
</script>

<style src="~/assets/styles/main.scss" lang="scss"></style>
