<template>
  <div class="about mt-6">
    <h1 class="font-bold text-4xl uppercase mb-6 flex">
      <svg-icon
        name="tag"
        class="text-gray-900 fill-current mr-2 mt-3"
        width="30px"
        height="30px"
      />
      <span>
        Tag
      </span>
    </h1>
    <section class="w-full">
      <masonry :data="tagCard">
        <template v-slot="{ item }">
          <card-tag :data="item" />
        </template>
      </masonry>
    </section>
  </div>
</template>

<script>
import { tagCard } from '@/utils/fake'

export default {
  name: 'TagPage',
  components: {
    Masonry: () => import(/* webpackChuckName: "Masonry" */ '@/components/Masonry'),
    CardTag: () => import(/* webpackChuckName: "CardTag" */ '@/components/cards/CardTag')
  },
  setup () {
    return {
      tagCard
    }
  }
}
</script>

<style lang="scss"></style>
