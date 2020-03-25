<template>
  <header
    :id="`${key}-header`"
    class="relative text-3xl font-bold"
  >
    <slot>
      <div>&nbsp;</div>
    </slot>
    <button
      @click="onClose"
      type="button"
      aria-label="close"
      class="absolute right-0 top-0 text-2xl text-gray-600 font-bold px-2 -mt-2"
    >
      <span aria-hidden="true">&times;</span>
    </button>
  </header>
</template>

<script>
import { inject } from '@vue/composition-api'

export default {
  name: 'ModalHeader',

  props: {
    close: {
      type: Boolean,
      default: true
    }
  },

  setup (_, context) {
    const key = inject('key')
    const onClose = inject('onClose')

    return {
      key,
      onClose
    }
  }
}
</script>

<style lang="scss"></style>
