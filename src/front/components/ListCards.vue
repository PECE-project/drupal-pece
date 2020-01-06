<template>
  <ul
    :class="{ 'list-card--vertical': vertical }"
    class="list-card flex flex-wrap justify-between"
  >
    <li
      v-for="(item, index) in data"
      :key="index"
      :class="{ 'list-card__item--vertical': vertical }"
      class="list-card__item"
    >
      <slot :item="item" />
    </li>
    <li v-show="linkSeeMore" class="flex w-full justify-end">
      <a href="#" class="flex mt-6 hover:text-accent">
        <span class="text-xs mt-1 font-bold capitalize">{{ $t('see') }} {{ $t('more') }}</span>
        <svg-icon name="rightArrowThinLine" width="38px" height="26px" class="fill-current" />
      </a>
    </li>
  </ul>
</template>

<script>
export default {
  name: 'ListCards',
  props: {
    linkSeeMore: {
      type: String,
      default: ''
    },
    direction: {
      type: String,
      default: 'horizontal'
    },
    vertical: {
      type: Boolean,
      default: false
    },
    data: {
      type: Array,
      default () {
        return []
      }
    }
  }
}
</script>

<style lang="scss">
.list-card {
  margin-left: -1rem;
  &--vertical {
    @apply ml-0;
  }
  &__item {
    @apply w-full mb-4 pl-4;
    @screen sm {
      @apply w-1/2;
    }
    @screen md {
      @apply w-1/4;
    }
    &--vertical {
      @apply pl-0 w-full;
    }
  }
}
</style>
