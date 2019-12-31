<template>
  <ul :class="{ 'list-card--vertical': vertical }" class="list-card flex flex-wrap justify-between">
    <li v-show="linkSeeMore" class="flex w-full justify-end">
      <a href="#" class="flex mb-6 hover:text-accent">
        <span class="text-xs font-bold">SEE MORE</span>
        <svg
          class="self-center ml-2 fill-current"
          xmlns="http://www.w3.org/2000/svg"
          width="34.146"
          height="10.834"
          viewBox="0 0 34.146 10.834"
        >
          <path d="M33.8,171.047l-8.168-4.716a.7.7,0,0,0-.7,1.214l5.9,3.409H.7a.7.7,0,1,0,0,1.4H30.825l-5.9,3.406a.7.7,0,1,0,.7,1.214l8.168-4.716a.7.7,0,0,0,0-1.214Z" transform="translate(0 -166.237)" />
        </svg>
      </a>
    </li>
    <li
      v-for="index in data"
      :key="index"
      :class="{ 'list-card__item--vertical': vertical }"
      class="list-card__item"
    >
      <slot :item="index" />
    </li>
  </ul>
</template>

<script>
export default {
  name: 'ListCards',
  props: {
    linkSeeMore: {
      type: String,
      default: null
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
    @apply ml-0 flex-col-reverse;
  }
  &__item {
    @apply w-1/2 mb-4 pl-4;
    @screen md {
      @apply w-1/4 mb-0;
    }
    &--vertical {
      @apply pl-0 w-full mb-4;
    }
  }
}
</style>
