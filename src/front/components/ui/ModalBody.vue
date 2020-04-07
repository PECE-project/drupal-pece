<template>
  <div :id="`${key}-body`">
    <slot />
  </div>
</template>

<script>
import { inject } from '@vue/composition-api'

export default {
  name: 'ModalBody',

  setup (_, context) {
    const key = inject('key')

    return {
      key
    }
  }
}
</script>

<style lang="scss"></style>
