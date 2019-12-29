<template>
  <div class="home flex mt-6 sm:mt-12 flex-wrap lg:flex-no-wrap">
    <div class="content sm:pr-0 lg:pr-6 w-full lg:w-3/4">
      <section class="highlights">
        <highlights />
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
    Highlights: () => import(/* webpackChunkName: "Highlights" */ '@/components/Highlights')
  }
}
</script>

<style lang="scss"></style>
