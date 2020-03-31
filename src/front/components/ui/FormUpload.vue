<template>
  <div
    class="form-upload border rounded border-gray-300"
    data-browse="Browse"
    data-placeholder="Choose a file or drop it here"
  >
    <!-- eslint-disable vue-a11y/form-has-label -->
    <input
      v-on="$listeners"
      v-bind="$attrs"
      @change="$emit('input', $event.target.files[0])"
      :class="{ 'border-red-500': error }"
      type="file"
      class="opacity-0 w-full p-2"
    >
  </div>
</template>

<script>
export default {
  name: 'Upload',

  inheritAttrs: false,

  props: {
    error: {
      type: Boolean,
      default: false
    }
  }
}
</script>

<style lang="scss">
.form-upload {
  position: relative;

  > input {
    position: relative;
    z-index: 4;
    cursor: pointer
  }

  &:before {
    content: attr(data-placeholder);
    top: 50%;
    transform: translateY(-50%);
    left: 10px;
  }

  &:after {
    @apply bg-gray-200;
    content: attr(data-browse);
    bottom: 0;
    right: 0;
    z-index: 3;
    display: block;
    border-left: inherit;
    padding: 12px 14px;
    font-family: inherit;
    font-size: 14px;
    height: 100%;
  }

  &:before, &:after {
    @apply text-gray-600;
    position: absolute;
  }
}
</style>
