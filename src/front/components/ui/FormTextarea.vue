<template>
  <!-- eslint-disable vue-a11y/form-has-label -->
  <textarea
    @input="$emit('update', $event.target.value)"
    :class="{ 'border-red-500': error }"
    class="w-full border border-gray-300 rounded p-2"
  />
</template>

<script>
export default {
  name: 'FormTextarea',

  model: {
    event: 'update'
  },

  props: {
    error: {
      type: Boolean,
      default: false
    }
  }
}
</script>

<style lang="scss"></style>
