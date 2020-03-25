<template>
  <span
    v-show="errors.length"
    class="text-red-700 text-xs"
  >
    <slot>
      {{ errors[0] }}
    </slot>
  </span>
</template>

<script>
export default {
  name: 'FormErrorMessage',

  props: {
    errors: {
      type: Array,
      required: true
    }
  }

  // TODO: Usar watch na errors para a próxima versão do vue-announcer (usar com o politeness "assertive")
}
</script>

<style lang="scss"></style>
