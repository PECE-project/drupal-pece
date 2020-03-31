<template functional>
  <hr :class="`border-${props.color} my-2`">
</template>

<script>
export default {
  name: 'Divider',

  props: {
    color: {
      type: String,
      default: 'gray-200'
    }
  }
}
</script>
