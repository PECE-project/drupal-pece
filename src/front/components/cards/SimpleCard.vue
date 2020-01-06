<template>
  <div class="simple-card rounded overflow-hidden shadow-pece flex flex-wrap flex-col h-full">
    <div :class="{ 'flex-auto': !data.image }" class="card__media">
      <nuxt-link :to="{ name: `group___${$i18n.locale}`, params: { slug: data.slug } }">
        <img v-if="data.image" :src="data.image.url" :alt="data.image.alt" class="w-full block">
        <div v-else class="bg-accent w-full h-full" />
      </nuxt-link>
    </div>
    <div class="card__content p-3 pb-4 min-h-12">
      <!-- eslint-disable-next-line vue/require-component-is -->
      <component :is="heading" class="card__title text-sm font-bold text-gray-900 leading-tight">
        <nuxt-link :to="{ name: `group___${$i18n.locale}`, params: { slug: data.slug } }">
          {{ data.title }}
        </nuxt-link>
      </component>
    </div>
  </div>
</template>

<script>
export default {
  name: 'SimpleCard',
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
