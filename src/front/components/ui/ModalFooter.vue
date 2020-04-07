<template>
  <footer :id="`${key}-footer`">
    <slot />
  </footer>
</template>

<script>
import { inject } from '@vue/composition-api'

export default {
  name: 'ModalFooter',

  setup (_, context) {
    const key = inject('key')

    return {
      key
    }
  }
}
</script>

<style lang="scss"></style>
