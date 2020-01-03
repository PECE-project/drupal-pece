<template>
  <div class="analyze mt-6">
    <h1 class="font-bold text-4xl uppercase mb-6">
      {{ `${$t('structured')} ${$t('analyze')}` }}
    </h1>
    <section>
      <list-cards
        :data="new Array(4)"
        :vertical="true"
      >
        <template>
          <div class="analyze__item flex flex-wrap md:flex-no-wrap rounded overflow-hidden shadow-pece">
            <div class="w-full h-12 sm:h-auto sm:w-1/6 lg:w-1/12 bg-accent flex justify-center">
              <svg-icon name="help" width="30px" height="30px" fill="white" class="self-center" />
            </div>
            <div class="content p-4 w-full sm:w-5/6 lg:w-11/12">
              <h2 class="font-bold text-lg leading-tight mb-2 sm:text-text-xl">
                <nuxt-link
                  :to="{ name: `questions_structured_analyze___${$i18n.locale}`, params: { slug: 'questions-test' } }"
                  class="hover:underline"
                >
                  Analyzing Representations of "Local Knowledge" in Tech Development
                </nuxt-link>
              </h2>
              <p class="text-sm">
                This analytic set of questions was developed by Angela Okune (UC Irvine Anthropology) and Leah Horgan (UC Irvine Informatics) to query a range of multimedia artifacts related to technology development in the "global South".
              </p>
            </div>
          </div>
        </template>
      </list-cards>
    </section>
  </div>
</template>

<script>
export default {
  name: 'Analyze',
  components: {
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards')
  }
}
</script>

<style lang="scss"></style>
