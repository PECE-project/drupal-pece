<template>
  <div>
    <the-heading />
    <nuxt />
  </div>
</template>

<script>
import TheHeading from '@/components/layout/TheHeading'

export default {
  components: {
    TheHeading
  },
  head () {
    return {
      ...this.$nuxtI18nSeo()
    }
  }
}
</script>

<style src="~/assets/styles/main.scss" lang="scss"></style>
