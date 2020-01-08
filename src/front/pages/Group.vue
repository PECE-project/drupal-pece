<template>
  <div class="group mt-6">
    <h1 class="font-bold text-4xl uppercase mb-6">
      {{ item.title }}
    </h1>
    <div class="flex flex-wrap lg:flex-no-wrap">
      <section class="w-full order-2 lg:order-1 lg:w-4/6">
        <tabs :uppercase="true">
          <tab label="Description">
            <p>
              This working group facilitates an ongoing collaborative interest shared by Leah Horgan and Angela Okune into scalar analyses of technology development, especially as described and practiced by mobile technology and design initiatives
            </p>
          </tab>
          <tab :label="$t('artifacts')">
            <list-cards :data="simpleCardData" :vertical="true">
              <template v-slot="{ item }">
                <horizontal-card :data="item" />
              </template>
            </list-cards>
          </tab>
          <tab :label="$t('essays')">
            <list-cards :data="simpleCardData" :vertical="true">
              <template v-slot="{ item }">
                <horizontal-card :data="item" />
              </template>
            </list-cards>
          </tab>
        </tabs>
      </section>
      <section class="w-full order-1 lg:order-2 mb-10 pr-0 lg:mt-0 lg:w-2/6 lg:pl-8 xl:pl-12">
        <div class="group__btn-request mb-6">
          <button type="button" class="link-accent w-full capitalize  py-6 rounded-sm">
            {{ $t('request_group_button') }}
          </button>
        </div>
        <div v-if="item.image" class="group__cover mb-6">
          <img :src="item.image.url" :alt="item.image.alt">
        </div>
        <div class="mt-3">
          <h2 class="uppercase font-bold text-3xl mb-4 leading-none">
            {{ item.title }} {{ $t('members') }}
          </h2>
          <list-users :users="users" :horizontal="true" />
        </div>
      </section>
    </div>
  </div>
</template>

<script>
import { simpleCardData, users } from '@/utils/fake'

export default {
  name: 'Group',
  components: {
    Tabs: () => import(/* webpackChunkName: "tabs" */ '@/components/tabs/Tabs'),
    Tab: () => import(/* webpackChunkName: "tab" */ '@/components/tabs/Tab'),
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards'),
    ListUsers: () => import(/* webpackChunkName: "ListUsers" */ '@/components/ListUsers'),
    HorizontalCard: () => import(/* webpackChunkName: "HorizontalCard" */ '@/components/cards/HorizontalCard')
  },
  setup (_, { root }) {
    return {
      simpleCardData,
      item: simpleCardData.find(item => item.slug === root.$route.params.slug),
      users
    }
  }
}
</script>

<style lang="scss"></style>
