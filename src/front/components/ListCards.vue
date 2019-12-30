<template>
  <ul class="list-card flex flex-wrap justify-between">
    <li v-for="index in Array(4)" :key="index" class="list-card__item pl-4 w-1/2 mb-4 md:w-1/4 md:mb-0">
      <card />
    </li>
  </ul>
</template>

<script>
export default {
  name: 'ListCards',
  components: {
    Card: () => import(/* webpackChunkName: "Card" */ '@/components/Card')
  }
}
</script>

<style lang="scss">
.list-card {
  margin-left: -1rem;
}
</style>
