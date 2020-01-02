<template>
  <form role="search" class="search relative flex justify-end">
    <label
      :class="{ 'search__label--active': term || searchFocused }"
      for="search"
      class="search__label w-2/3 lg:w-2/5 border border-gray-100"
    >
      <span class="sr-only">{{ $t('a11y.text_search') }}</span>
      <input
        id="search"
        v-model="term"
        @focus="searchFocused = true"
        @blur="searchFocused = false"
        :placeholder="$t('search')"
        class="shadow-pece p-4 pr-12 w-full"
        type="text"
        name="search"
      >
    </label>
    <button class="absolute p-2 px-4 right-0 inset-y-0 flex items-center justify-center">
      <span class="sr-only">{{ $t('a11y.submit_search') }}</span>
      <svg-icon name="search" width="20px" height="20px" class="text-gray-600 fill-current" />
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
