<template>
  <form role="search" class="search relative flex justify-end">
    <label
      :class="{ 'search__label--active': term || searchFocused }"
      for="search"
      class="search__label md:w-3/5 lg:w-2/5"
    >
      <span class="sr-only">{{ $t('a11y.text_search') }}</span>
      <input
        id="search"
        v-model="term"
        @focus="searchFocused = true"
        @blur="searchFocused = false"
        class="shadow-pece p-3 pr-12 w-full"
        placeholder="Search"
        type="text"
        name="search"
      >
    </label>
    <button class="absolute p-2 px-4 right-0 inset-y-0 flex items-center justify-center">
      <span class="sr-only">{{ $t('a11y.submit_search') }}</span>
      <svg
        class="fill-current text-gray-600"
        xmlns="http://www.w3.org/2000/svg"
        width="16.832"
        height="17.434"
        viewBox="0 0 16.832 17.434"
      >
        <path d="M17.56,15.88l-4.149-4.316a7.036,7.036,0,1,0-5.388,2.514A6.964,6.964,0,0,0,12.056,12.8l4.181,4.348A.918.918,0,1,0,17.56,15.88ZM8.023,1.836a5.2,5.2,0,1,1-5.2,5.2A5.209,5.209,0,0,1,8.023,1.836Z" transform="translate(-0.984)" />
      </svg>
    </button>
  </form>
</template>

<script>
import { reactive, toRefs } from '@vue/composition-api'

export default {
  name: 'Search',
  setup () {
    const state = reactive({
      term: '',
      searchFocused: false
    })
    return {
      ...toRefs(state)
    }
  }
}
</script>

<style lang="scss">
.search {
  &__label {
    transition: width .5s;
    &--active {
      @apply w-full;
    }
  }
}
</style>
