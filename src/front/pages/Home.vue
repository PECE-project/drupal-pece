<template>
  <div class="home flex mt-6 sm:mt-12 flex-wrap lg:flex-no-wrap">
    <div class="content sm:pr-0 lg:pr-6 w-full lg:w-3/4">
      <section class="highlights">
        <highlights />
      </section>
      <section class="tabs">
        <tabs />
      </section>
      <section class="about bg-gray-100 mt-6 md:mt-12 p-8 sm:p-12 flex flex-wrap lg:flex-no-wrap">
        <div class="w-full lg:w-2/5">
          <img src="~/assets/images/logo-pece-ico.png" alt="Logo PECE project" class="w-12">
          <h1 class="mt-4 text-2xl lg:text-3xl font-bold sm:pr-2 leading-tight">
            Platform for Experimental, Collaborative Ethnography
          </h1>
        </div>
        <div class="w-full lg:w-3/5 text-sm">
          <p class="my-6 lg:mt-16">
            (PECE: pronounced “peace”) Is an open source (Drupal-based) digital platform that supports multi-sited, cross-scale ethnographic and historical research. The platform links researchers in new ways, enables new kinds of analyses and data visualization, and activates researchers’ engagement with public problems and diverse audiences. PECE is at the center of a research project that explores how digital infrastructure can be designed to support collaborative hermeneutics....
          </p>
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
    Tabs: () => import(/* webpackChunkName: "tabs" */ '@/components/Tabs')
  }
}
</script>

<style lang="scss"></style>
