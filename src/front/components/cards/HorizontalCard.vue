<template>
  <div class="horizontal-card flex rounded overflow-hidden shadow-pece">
    <div class="horizontal-card__media">
      <nuxt-link :to="data.to" class="h-full">
        <img v-if="data.image" :src="data.image.url" :alt="data.image.alt" class="w-full h-full object-cover">
        <div v-else :aria-label="data.title" class="bg-accent w-full h-full" />
      </nuxt-link>
    </div>
    <div class="horizontal-card__content w-3/3 px-3 self-center">
      <h2 class="card__title text-sm font-bold text-gray-900 leading-tight">
        <nuxt-link :to="data.to" class="hover:text-accent">
          {{ data.title }}
        </nuxt-link>
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
    height: 100px;
  }
}
</style>
