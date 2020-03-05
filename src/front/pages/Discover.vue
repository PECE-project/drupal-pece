<template>
  <div class="discover mt-6">
    <h1 class="font-bold text-4xl uppercase mb-6">
      {{ $t('repository') }}
    </h1>
    <div class="flex flex-wrap lg:flex-no-wrap">
      <section class="w-full order-2 lg:order-1 lg:w-4/6">
        <list-cards :data="discoverData">
          <template v-slot="{ item }">
            <simple-card :data="item" />
          </template>
        </list-cards>
      </section>
      <section class="w-full order-1 lg:order-2 mb-10 pr-0 lg:mt-0 lg:w-2/6 lg:pl-8 xl:pl-12">
        <a href="#" class="uppercase text-2xl text-accent hover:underline">
          {{ $t('bibliography') }}
        </a>
        <form name="search-repo" class="mt-4">
          <label for="search">
            <input
              id="search_discover"
              v-model="term"
              :placeholder="`${$t('search')}`"
              class="shadow-pece p-4 pr-12 border border-gray-100 w-full"
              type="text"
              name="search"
            >
          </label>
          <list-filter :items="filterItems" @chosen="setFilter" />
          <button type="button" class="link-accent mt-4 rounded-sm">
            Apply
          </button>
        </form>
      </section>
    </div>
  </div>
</template>

<script>
import { reactive, toRefs } from '@vue/composition-api'

import { filter as filterItems, discoverData } from '@/utils/fake'

export default {
  name: 'DiscoverPage',
  components: {
    ListFilter: () => import(/* webpackChunkName: "ListFilter" */ '@/components/ListFilter'),
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards'),
    SimpleCard: () => import(/* webpackChunkName: "SimpleCard" */ '@/components/cards/SimpleCard')
  },
  setup () {
    const state = reactive({
      term: '',
      filters: []
    })

    function setFilter (item) {
      state.filters = [...state.filters, item]
    }

    return {
      ...toRefs(state),
      filterItems,
      setFilter,
      discoverData
    }
  }
}
</script>

<style lang="scss"></style>
