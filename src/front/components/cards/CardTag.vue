<template>
  <article class="card-tag p-3 bg-gray-100 rounded shadow-gray100">
    <header class="mb-3">
      <div class="card-tag__icon flex justify-end">
        <svg-icon
          :name="icons[data.__typename]"
          class="text-gray-600 fill-current"
          width="20px"
          height="20px"
        />
      </div>
      <h2 class="uppercase mt-3 pt-3 text-lg leading-tight font-bold border-t border-solid border-gray-300">
        {{ data.title }}
      </h2>
    </header>
    <section class="mb-3">
      <p>
        {{ data.body }}
      </p>
      <nuxt-link :to="data.to" class="capitalize text-sm mt-2 block text-accent hover:underline">
        {{ $t('read_more') }}
      </nuxt-link>
    </section>
    <aside />
  </article>
</template>

<script>
// Temp code for transform icon name
import { icons } from '@/utils/fake'

export default {
  name: 'CardTag',
  props: {
    data: {
      type: Array,
      required: true
    }
  },
  setup () {
    return {
      icons
    }
  }
}
</script>

<style lang="scss"></style>
