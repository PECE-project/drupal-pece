<template>
  <ul class="masonry">
    <li
      v-for="(item, index) in data"
      :key="`masonry__${index}`"
      class="masonry__item"
    >
      <slot :item="item" />
    </li>
  </ul>
</template>

<script>
export default {
  name: 'Masonry',
  props: {
    data: {
      type: Array,
      required: true
    }
  }
}
</script>

<style lang="scss">
.masonry {
  display: flex;
  flex-wrap: wrap;
  align-content: space-between;
  min-height: 800px;

  @screen sm {
    flex-flow: column wrap;
    height: 1000px; // See if you can make it dynamic
  }

  &__item {
    width: 100%;
    margin-bottom: 2%;

    @screen sm {
      width: 32%;

      &:nth-child(3n+1) { order: 1; }
      &:nth-child(3n+2) { order: 2; }
      &:nth-child(3n)   { order: 3; }
    }
  }

  &::before, &::after {
    content: "";
    flex-basis: 100%;
    width: 0;
    order: 2;
  }
}
</style>
