<template>
  <!-- eslint-disable vue-a11y/label-has-for -->
  <label class="font-bold">
    <span>
      <slot />
    </span>
    <span
      v-show="required"
      class="text-red-700 text-sm"
    >*</span>
  </label>
</template>

<script>
import { inject } from '@vue/composition-api'

export default {
  name: 'FormLabel',

  setup () {
    const required = inject('required')

    return {
      required
    }
  }
}
</script>

<style lang="scss"></style>
