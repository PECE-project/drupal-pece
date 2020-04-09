<template>
  <div class="about mt-6">
    <h1 class="font-bold text-4xl uppercase mb-6">
      {{ $t('about') }}
    </h1>
    <section>
      <tabs :uppercase="true">
        <tab label="Projects">
          <list-cards :data="simpleCardData" :vertical="true">
            <template v-slot="{ item }">
              <horizontal-card :data="item" />
            </template>
          </list-cards>
        </tab>
        <tab :label="$t('people')">
          <list-cards :data="simpleCardData" :vertical="true">
            <template v-slot="{ item }">
              <horizontal-card :data="item" />
            </template>
          </list-cards>
        </tab>
        <tab label="substantive logics">
          <list-cards :data="simpleCardData" :vertical="true">
            <template v-slot="{ item }">
              <horizontal-card :data="item" />
            </template>
          </list-cards>
        </tab>
        <tab label="design logics">
          <list-cards :data="simpleCardData" :vertical="true">
            <template v-slot="{ item }">
              <horizontal-card :data="item" />
            </template>
          </list-cards>
        </tab>
        <tab :label="$t('about')" class="about__content">
          <div v-html="about.body" />
        </tab>
      </tabs>
    </section>
  </div>
</template>

<script>
import { simpleCardData } from '@/utils/fake'
import useRoute from '@/graphql/composables/useRoute'
import { GET_ROUTE } from '@/graphql/queries/route'

export default {
  name: 'About',
  components: {
    Tabs: () => import(/* webpackChunkName: "tabs" */ '@/components/tabs/Tabs'),
    Tab: () => import(/* webpackChunkName: "tab" */ '@/components/tabs/Tab'),
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards'),
    HorizontalCard: () => import(/* webpackChunkName: "HorizontalCard" */ '@/components/cards/HorizontalCard')
  },
  setup () {
    const { data: about } = useRoute({
      query: GET_ROUTE,
      variables: { path: '/about' }
    })

    return {
      about,
      simpleCardData
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
