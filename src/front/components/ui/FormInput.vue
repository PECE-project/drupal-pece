<template>
  <!-- eslint-disable vue-a11y/form-has-label -->
  <input
    :type="type"
    v-on="$listeners"
    v-bind="$attrs"
    @input="$emit('update', $event.target.value)"
    :class="{ 'border-red-500': error }"
    class="w-full border border-gray-300 rounded p-2"
  >
</template>

<script>
export default {
  name: 'FormInput',

  inheritAttrs: false,

  model: {
    event: 'update'
  },

  props: {
    type: {
      type: String,
      default: 'text'
    },
    error: {
      type: Boolean,
      default: false
    }
  }
}
</script>

<style lang="scss"></style>
