<template>
  <ValidationObserver v-slot="{ invalid, passed, validate }" slim>
    <form @submit.prevent="validate().then($emit('submitted', passed))">
      <slot :invalid="invalid" />
    </form>
  </ValidationObserver>
</template>

<script>
import { ValidationObserver } from 'vee-validate'

export default {
  name: 'FormControl',

  components: {
    ValidationObserver
  }
}
</script>

<style lang="scss"></style>
