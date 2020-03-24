<template>
  <ValidationProvider
    v-slot="{ errors }"
    :rules="rules"
    tag="div"
  >
    <slot :errors="errors" />
  </ValidationProvider>
</template>

<script>
import { ValidationProvider } from 'vee-validate'

export default {
  name: 'FormControlValidate',

  components: {
    ValidationProvider
  },

  props: {
    rules: {
      type: String,
      required: true
    }
  }
}
</script>

<style lang="scss"></style>
