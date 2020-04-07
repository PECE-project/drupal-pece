<template>
  <nuxt-link
    :to="data.to"
    :class="`tag rounded-full bg-gray-100 text-gray-600 p-1 px-3 mr-1 text-${size} hover:bg-gray-300 hover:underline`"
  >
    {{ data.title }}
  </nuxt-link>
</template>

<script>
export default {
  name: 'Tag',
  props: {
    data: {
      type: Object,
      required: true
    },
    size: {
      type: String,
      default: 'base'
    }
  }
}
</script>

<style lang="scss"></style>
