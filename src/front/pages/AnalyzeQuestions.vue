<template>
  <div class="analyze-questions mt-6">
    <h1 class="font-bold text-4xl leading-tight uppercase mb-6 text-gray-900">
      <svg-icon
        name="help"
        width="30px"
        height="30px"
        class="text-gray-900 currentColor inline"
        aria-hidden="true"
      />
      <span>ANALYZING REPRESENTATIONS OF "LOCAL KNOWLEDGE" IN TECH DEVELOPMENT</span>
    </h1>
    <section>
      <list-cards
        :data="new Array(4)"
        :vertical="true"
      >
        <template>
          <div class="analyze__item flex flex-wrap md:flex-no-wrap rounded overflow-hidden shadow-pece">
            <div class="content p-4 w-full sm:w-5/6 lg:w-11/12">
              <h2 class="font-bold leading-tight mb-3 text-lg sm:text-text-xl">
                <nuxt-link
                  :to="{ name: `questions_structured_analyze___${$i18n.locale}`, params: { slug: 'questions-test' } }"
                  class="hover:underline"
                >
                  META: What common narratives does the creator leverage to characterize tech development? (How) are histories and contextual factors pointed to?
                </nuxt-link>
              </h2>
              <div class="text-sm">
                Submitted by
                <a href="#" class="text-accent hover:underline">
                  Angela Okune
                </a>
                on August 13, 2018 - 6:10pm
              </div>
            </div>
          </div>
        </template>
      </list-cards>
    </section>
  </div>
</template>

<script>
export default {
  name: 'AnalyzeQuestions',
  components: {
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards')
  }
}
</script>

<style lang="scss"></style>
