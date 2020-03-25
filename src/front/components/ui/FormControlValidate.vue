<template>
  <ValidationProvider
    v-slot="{ errors }"
    :rules="rules"
    :name="name"
    tag="div"
    role="group"
  >
    <slot :errors="errors" />
  </ValidationProvider>
</template>

<script>
import { provide } from '@vue/composition-api'

import { ValidationProvider } from 'vee-validate'

export default {
  name: 'FormControlValidate',

  components: {
    ValidationProvider
  },

  props: {
    name: {
      type: String,
      required: true
    },
    rules: {
      type: String,
      required: true
    }
  },

  setup ({ rules }) {
    if (rules.includes('required')) {
      provide('required', true)
    }
  }
}
</script>

<style lang="scss"></style>
