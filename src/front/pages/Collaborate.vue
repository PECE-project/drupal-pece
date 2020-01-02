<template>
  <div class="collaborate mt-6">
    <h1 class="font-bold text-4xl uppercase mb-6">
      {{ $t('collaborate') }}
    </h1>
    <div class="flex flex-wrap lg:flex-no-wrap">
      <section class="w-full order-2 lg:order-1 lg:w-4/6">
        <list-cards :data="new Array(8)">
          <template v-slot="{ item }">
            <simple-card :data="{ item }" />
          </template>
        </list-cards>
      </section>
      <section class="w-full order-1 lg:order-2 mb-10 pr-0 lg:mt-0 lg:w-2/6 lg:pl-8 xl:pl-12">
        <form name="search-groups">
          <label for="search" class="border border-gray-100">
            <input
              id="search"
              v-model="term"
              :placeholder="`${$t('search')} ${$t('groups').toLowerCase()}`"
              class="shadow-pece p-4 pr-12 w-full"
              type="text"
              name="search"
            >
          </label>
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

export default {
  name: 'About',
  components: {
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards'),
    SimpleCard: () => import(/* webpackChunkName: "SimpleCard" */ '@/components/cards/SimpleCard')
  },
  setup () {
    const state = reactive({
      term: ''
    })

    return {
      ...toRefs(state)
    }
  }
}
</script>

<style lang="scss">
.about {
  &__content {
    p {
      @apply mb-3;
    }
    h2 {
      @apply font-bold text-lg mb-3 mt-8;
    }
    ul {
      @apply list-disc ml-5;
      li {
        @apply mb-2;
      }
    }
  }
}
</style>
