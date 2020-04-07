<template>
  <div role="group">
    <slot />
  </div>
</template>

<script>
import { provide } from '@vue/composition-api'

export default {
  name: 'FormControl',
  setup () {
    provide('required', false)
  }
}
</script>

<style lang="scss"></style>
