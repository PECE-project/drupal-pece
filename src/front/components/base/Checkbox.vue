<template>
  <label
    :for="id"
    :class="{ 'base-checkbox--error': error }"
    class="base-checkbox relative cursor-pointer flex"
  >
    <div class="base-checkbox__box-input relative w-4 self-center">
      <!-- eslint-disable-next-line vue-a11y/form-has-label -->
      <input
        :id="id"
        v-on="$listeners"
        v-bind="$attrs"
        @change="$emit('update', $event.target.checked)"
        type="checkbox"
        class="base-checkbox__input relative z-20 opacity-0"
      >
      <span class="base-checkbox__square absolute w-4 h-4 z-10 left-0 rounded-sm border border-gray-600 border-solid block" />
    </div>
    <div class="relative font-bold text-sm text-gray-900 ml-2 self-center">
      <slot name="label">
        {{ label }}
      </slot>
    </div>
    <div class="base-checkbox__validation absolute text-red-400 text-xs hidden">
      <slot name="validation" />
    </div>
  </label>
</template>

<script>
export default {
  name: 'BaseCheckbox',
  inheritAttrs: false,
  model: {
    event: 'update'
  },
  props: {
    id: {
      type: String,
      required: true
    },
    error: {
      type: Boolean,
      default: false
    },
    label: {
      type: String,
      default: ''
    }
  }
}
</script>

<style lang="scss">
.base-checkbox {
  &__input {
    &:checked + .base-checkbox__square {
      &:before {
        @apply block;
      }
    }
  }

  &__square {
    top: 4px;
    transition: all .2s ease-in-out;

    &:before {
      @apply absolute border-accent border-solid hidden;
      content: '';
      top: 2px;
      left: 5px;
      width: 4px;
      height: 10px;
      border-width: 0 2px 2px 0;
      transform: rotate(45deg);
    }
  }

  &__validation {
    width: max-content;
    bottom: -18px;
    left: 16px;
  }

  &--error {
    .base-checkbox__box-input {
      @apply border-red-400;
    }
    .base-checkbox__square {
      @apply border border-solid border-red-400;
    }
    .base-checkbox__validation {
      @apply inline-block;
    }
  }
}
</style>
