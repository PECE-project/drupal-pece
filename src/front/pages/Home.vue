<template>
  <div class="home flex mt-6 sm:mt-12 flex-wrap lg:flex-no-wrap">
    <div class="content w-full lg:w-4/6">
      <section class="highlights">
        <highlights />
      </section>
      <section class="tabs mt-12 md:mt-16">
        <tabs :uppercase="true">
          <tab :label="$t('recent_essays')">
            <list-cards :data="new Array(4)">
              <template v-slot="{ item }">
                <card :data="{ item }" />
              </template>
            </list-cards>
          </tab>
          <tab :label="$t('recent_artifacts')">
            <h3>CONTENT TAB</h3>
          </tab>
        </tabs>
      </section>
      <section class="about bg-gray-100 mt-12 md:mt-16 p-8 sm:p-12 flex flex-wrap lg:flex-no-wrap">
        <div class="w-full lg:w-2/5">
          <img src="~/assets/images/logo-pece-ico.png" alt="Logo PECE project" class="w-12">
          <h1 class="mt-4 text-2xl lg:text-3xl font-bold sm:pr-2 leading-tight">
            {{ $t('project_title') }}
          </h1>
        </div>
        <div class="w-full lg:w-3/5 text-sm">
          <p v-html="$t('project_description')" class="my-6 lg:mt-16" />
          <a href="#" class="link-accent-transparent uppercase text-xs font-bold">
            {{ $t('read_more') }}
          </a>
        </div>
      </section>
    </div>
    <div class="sidebar w-full mt-12 pr-0 lg:mt-0 lg:w-2/6 lg:pl-8 xl:pl-12">
      <tabs :uppercase="true">
        <tab :label="$t('groups')">
          <list-cards :data="new Array(4)" :vertical="true">
            <template v-slot="{ item }">
              <horizontal-card :data="{ item }" />
            </template>
          </list-cards>
        </tab>
        <tab :label="$t('people')">
          <h3>CONTENT TAB</h3>
        </tab>
      </tabs>
    </div>
  </div>
</template>

<script>
export default {
  name: 'Home',
  components: {
    Highlights: () => import(/* webpackChunkName: "Highlights" */ '@/components/Highlights'),
    Tabs: () => import(/* webpackChunkName: "tabs" */ '@/components/tabs/Tabs'),
    Tab: () => import(/* webpackChunkName: "tab" */ '@/components/tabs/Tab'),
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards'),
    Card: () => import(/* webpackChunkName: "Card" */ '@/components/cards/Card'),
    HorizontalCard: () => import(/* webpackChunkName: "HorizontalCard" */ '@/components/cards/HorizontalCard')
  }
}
</script>

<style lang="scss"></style>
