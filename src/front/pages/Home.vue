<template>
  <div class="home flex mt-6 sm:mt-12 flex-wrap lg:flex-no-wrap">
    <div class="content sm:pr-0 lg:pr-6 w-full lg:w-3/4">
      <section class="highlights">
        <highlights />
      </section>
      <section class="tabs mt-6 md:mt-16">
        <tabs :uppercase="true">
          <tab :label="$t('recent_essays')">
            <list-cards />
          </tab>
          <tab :label="$t('recent_artifacts')">
            <list-cards />
          </tab>
        </tabs>
      </section>
      <section class="about bg-gray-100 mt-6 md:mt-16 p-8 sm:p-12 flex flex-wrap lg:flex-no-wrap">
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
    <div class="sidebar w-full lg:w-1/4">
      SIDEBAR
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
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards')
  }
}
</script>

<style lang="scss"></style>
