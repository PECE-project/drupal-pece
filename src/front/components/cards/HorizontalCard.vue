<template>
  <div class="horizontal-card flex rounded overflow-hidden shadow-pece">
    <div class="horizontal-card__media">
      <a href="#">
        <img src="~/assets/images/media/1067-320x200.jpg" alt="Description image" class="object-contain">
      </a>
    </div>
    <div class="horizontal-card__content w-3/3 px-3 self-center">
      <h2 class="card__title text-sm font-bold text-gray-900 leading-tight">
        <a href="#" class="hover:text-accent">
          Empirical humanities metadata wg
        </a>
      </h2>
    </div>
  </div>
</template>

<script>
export default {
  name: 'HorizontalCard',
  props: {
    data: {
      type: Object,
      required: true
    }
  }
}
</script>

<style lang="scss">
.horizontal-card {
  &__media {
    width: 100px;
  }
}
</style>
