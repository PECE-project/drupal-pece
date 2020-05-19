<template>
  <div class="home flex mt-6 sm:mt-12 flex-wrap lg:flex-no-wrap">
    <div class="content w-full lg:w-4/6">
      <section class="highlights">
        <highlights />
      </section>
      <section class="tabs mt-12 md:mt-16">
        <tabs :uppercase="true">
          <tab :label="$t('recent_essays')">
            <ListCards :data="getEssays" v-if="getEssays.length">
              <template v-slot="{ item }">
                <card :data="item" />
              </template>
            </ListCards>
          </tab>
          <tab :label="$t('recent_artifacts')">
            <h3>CONTENT TAB</h3>
          </tab>
        </tabs>
      </section>
      <section
        v-if="home"
        class="about bg-gray-100 mt-12 md:mt-16 p-8 sm:p-12 flex flex-wrap lg:flex-no-wrap"
      >
        <div class="w-full lg:w-2/5">
          <img src="~/assets/images/logo-pece-ico.png" alt="Logo PECE project" class="w-12">
          <h1 class="mt-4 text-2xl lg:text-3xl font-bold sm:pr-2 leading-tight">
            {{ home.title }}
          </h1>
        </div>
        <div class="w-full lg:w-3/5 text-sm">
          <p v-if="home.body" v-html="home.body" class="my-6 lg:mt-16" />
          <nuxt-link
            :to="{ name: `about___${$i18n.locale}` }"
            class="link-accent-transparent uppercase text-xs font-bold"
          >
            {{ $t('read_more') }}
          </nuxt-link>
        </div>
      </section>
    </div>
    <div class="sidebar w-full mt-12 pr-0 lg:mt-0 lg:w-2/6 lg:pl-8 xl:pl-12">
      <tabs :uppercase="true">
        <tab :label="$t('groups')">
          <ListCards :data="simpleCardData" :vertical="true">
            <template v-slot="{ item }">
              <HorizontalCard :data="item" />
            </template>
          </ListCards>
        </tab>
        <tab :label="$t('people')">
          <ListUsers :users="getUsers" :horizontal="true" />
        </tab>
      </tabs>
    </div>
  </div>
</template>

<script>
import { simpleCardData } from '@/utils/fake'
import { computed } from '@vue/composition-api'
import useGqlContents from '@/graphql/composables/useGqlContents'
import useGqlRoute from '@/graphql/composables/useGqlRoute'
import { GET_ESSAYS_HOME } from '@/graphql/queries/essay'
import { GET_USERS } from '@/graphql/queries/user'
import { GET_ROUTE } from '@/graphql/queries/route'

export default {
  name: 'Home',

  components: {
    Tabs: () => import(/* webpackChunkName: "tabs" */ '@/components/tabs/Tabs'),
    Tab: () => import(/* webpackChunkName: "tab" */ '@/components/tabs/Tab'),
    Card: () => import(/* webpackChunkName: "Card" */ '@/components/cards/Card'),
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards'),
    ListUsers: () => import(/* webpackChunkName: "ListUsers" */ '@/components/ListUsers'),
    Highlights: () => import(/* webpackChunkName: "Highlights" */ '@/components/Highlights'),
    HorizontalCard: () => import(/* webpackChunkName: "HorizontalCard" */ '@/components/cards/HorizontalCard')
  },

  setup (_, { root }) {
    const { data: home } = useGqlRoute({
      query: GET_ROUTE,
      variables: { path: `/${root.$i18n.locale}/home` }
    })

    const { data: users } = useGqlContents({
      query: GET_USERS,
      variables: {
        offset: 0,
        limit: 10
      },
      type: 'users'
    })

    const { data } = useGqlContents({
      query: GET_ESSAYS_HOME,
      variables: {
        offset: 0,
        limit: 4
      },
      type: 'peceEssays'
    })

    const getEssays = computed(() => {
      if (data.value) {
        return data.value.map((essay) => {
          const tags = essay.tags && essay.tags.length
            ? essay.tags
              .filter(item => item.title)
              .map((item) => {
                return {
                  title: item.title,
                  to: {
                    name: `tag___${root.$i18n.locale}`,
                    params: {
                      slug: item.title
                    }
                  }
                }
              })
              .slice(0, 2)
            : []
          return {
            id: essay.id,
            title: essay.title,
            to: {
              name: `essay___${root.$i18n.locale}`,
              params: {
                id: essay.id
              }
            },
            author: {
              name: essay.author.username,
              to: {
                name: `user___${root.$i18n.locale}`,
                params: {
                  slug: essay.author.username
                }
              }
            },
            image: {
              alt: essay.thumbnail.alt,
              url: essay.thumbnail.url
            },
            tags,
            created: essay.created
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
      home,
      getUsers,
      getEssays,
      simpleCardData
    }
  }
}
</script>

<style lang="scss"></style>
