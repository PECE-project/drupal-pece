<template functional>
  <span
    v-show="props.errors.length"
    class="text-red-700 text-xs"
  >
    <slot>
      {{ props.errors[0] }}
    </slot>
  </span>
</template>

<script>
export default {
  name: 'FormErrorMessage',

  props: {
    errors: {
      type: Array,
      default () {
        return []
      }
    }
  }
}
</script>
