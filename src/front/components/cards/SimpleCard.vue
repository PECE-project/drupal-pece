<template>
  <div class="simple-card rounded overflow-hidden shadow-pece">
    <div class="card__media">
      <a href="#">
        <img src="~/assets/images/media/880-320x200.jpg" alt="Description image" class="w-full block">
      </a>
    </div>
    <div class="card__content p-3 pb-4">
      <!-- eslint-disable-next-line vue/require-component-is -->
      <component :is="heading" class="card__title text-sm font-bold text-gray-900 leading-tight">
        <a href="#">
          Open group
        </a>
      </component>
    </div>
  </div>
</template>

<script>
export default {
  name: 'Card',
  props: {
    data: {
      type: Object,
      required: true
    },
    heading: {
      type: String,
      default: 'h2'
    }
  }
}
</script>

<style lang="scss"></style>
