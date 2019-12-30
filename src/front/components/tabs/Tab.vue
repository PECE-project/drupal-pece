<template>
  <section
    role="tabpanel"
    class="pt-6"
    tabindex="-1"
    hidden
  >
    <slot />
  </section>
</template>

<script>
export default {
  name: 'Tab',
  props: {
    title: {
      type: String,
      required: true
    },
    disabled: {
      type: Boolean,
      default: false
    }
  }
}
</script>

<style lang="scss"></style>
