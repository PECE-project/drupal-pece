<template>
  <div class="simple-card rounded overflow-hidden shadow-pece">
    <div class="card__media">
      <a href="#">
        <img src="https://picsum.photos/320/200" alt="Description image" class="w-full block">
      </a>
    </div>
    <div class="card__content p-3 pb-4">
      <h2 class="card__title text-sm font-bold text-gray-900 leading-tight">
        <a href="#">
          Open group
        </a>
      </h2>
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
    }
  }
}
</script>

<style lang="scss"></style>
