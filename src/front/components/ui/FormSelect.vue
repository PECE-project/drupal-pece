<template>
  <select
    :class="{ 'border-red-500': error }"
    @blur="$emit('update', $event.target.value)"
    class="w-full border border-gray-300 rounded p-2"
  >
    <option v-show="placeholder" value>
      {{ placeholder }}
    </option>
    <slot />
  </select>
</template>

<script>
export default {
  name: 'FormSelect',

  model: {
    event: 'update'
  },

  props: {
    placeholder: {
      type: String,
      default: null
    },
    error: {
      type: Boolean,
      default: false
    }
  }
}
</script>
