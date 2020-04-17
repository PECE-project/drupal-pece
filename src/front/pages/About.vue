<template>
  <div class="about mt-6">
    <h1 class="font-bold text-4xl uppercase mb-6">
      {{ $t('about') }}
    </h1>
    <section>
      <tabs :uppercase="true">
        <tab label="Projects">
          <list-cards
            :data="getProjects"
            :vertical="true"
          >
            <template v-slot="{ item }">
              <horizontal-card :data="item" />
            </template>
          </list-cards>
        </tab>
        <tab :label="$t('people')">
          <ListUsers :users="getUsers" :horizontal="true" />
        </tab>
        <tab label="substantive logics">
          <list-cards
            :data="getSubstantiveLogics"
            :vertical="true"
          >
            <template v-slot="{ item }">
              <horizontal-card :data="item" />
            </template>
          </list-cards>
        </tab>
        <tab
          :label="$t('about')"
          class="about__content"
        >
          <div v-if="about" v-html="about.body" />
        </tab>
      </tabs>
    </section>
  </div>
</template>

<script>
import { simpleCardData } from '@/utils/fake'
import { GET_ROUTE } from '@/graphql/queries/route'
import { GET_PROJECTS_ABOUT } from '@/graphql/queries/project'
import { GET_SUBSTANTIVE_LOGICS_ABOUT } from '@/graphql/queries/substantiveLogics'
import useGqlRoute from '@/graphql/composables/useGqlRoute'
import useGqlContents from '../graphql/composables/useGqlContents'
import { computed } from '@vue/composition-api'
import { GET_USERS } from '@/graphql/queries/user'

export default {
  name: 'About',
  components: {
    Tabs: () => import(/* webpackChunkName: "tabs" */ '@/components/tabs/Tabs'),
    Tab: () => import(/* webpackChunkName: "tab" */ '@/components/tabs/Tab'),
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards'),
    ListUsers: () => import(/* webpackChunkName: "ListUsers" */ '@/components/ListUsers'),
    HorizontalCard: () => import(/* webpackChunkName: "HorizontalCard" */ '@/components/cards/HorizontalCard')
  },
  setup (_, { root }) {
    const { data: about } = useGqlRoute({
      query: GET_ROUTE,
      variables: { path: '/about' }
    })

    const variables = {
      offset: 0,
      limit: 10
    }

    const { data: users } = useGqlContents({
      query: GET_USERS,
      variables,
      type: 'users'
    })

    const { data: projects } = useGqlContents({
      query: GET_PROJECTS_ABOUT,
      variables,
      type: 'peceProjects'
    })

    const { data: substantiveLogics } = useGqlContents({
      query: GET_SUBSTANTIVE_LOGICS_ABOUT,
      variables,
      type: 'peceSubstantiveLogics'
    })

    const getProjects = computed(() => {
      if (projects.value) {
        return projects.value.map((project) => {
          return {
            id: project.id,
            title: project.title,
            slug: project.id,
            to: {
              name: `project___${root.$i18n.locale}`,
              params: {
                slug: project.id
              }
            },
            image: project.image.url
              ? {
                alt: project.image.alt,
                url: project.image.url
              }
              : null
          }
        })
      }
      return []
    })

    const getSubstantiveLogics = computed(() => {
      if (substantiveLogics.value) {
        return substantiveLogics.value.map((sub) => {
          return {
            id: sub.id,
            title: sub.title,
            slug: sub.id,
            to: {
              name: `substantive_logics___${root.$i18n.locale}`,
              params: {
                slug: sub.id
              }
            },
            image: sub.thumbnail.url
              ? {
                alt: sub.thumbnail.alt,
                url: sub.thumbnail.url
              }
              : null
          }
        })
      }
      return []
    })

    const getUsers = computed(() => {
      if (users.value) {
        return users.value.map((user) => {
          return {
            id: user.id,
            fullname: user.mail,
            slug: user.username
          }
        })
      }
      return []
    })

    return {
      getUsers,
      getProjects,
      getSubstantiveLogics,
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
