<template>
  <div v-if="users.length" class="list-users">
    <list-cards :data="users" :vertical="true">
      <template v-slot="{ item }">
        <horizontal-card :data="prepareData(item)" />
      </template>
    </list-cards>
  </div>
</template>

<script>
export default {
  name: 'ListUsers',
  components: {
    ListCards: () => import(/* webpackChunkName: "ListCards" */ '@/components/ListCards'),
    HorizontalCard: () => import(/* webpackChunkName: "HorizontalCard" */ '@/components/cards/HorizontalCard')
  },
  props: {
    horizontal: {
      type: Boolean,
      default: true
    },
    users: {
      type: Array,
      default () {
        return []
      }
    }
  },
  setup (_, { root }) {
    function prepareData (item) {
      const nameRoute = `user___${root.$i18n.locale}`
      return {
        title: item.fullname,
        to: {
          name: nameRoute,
          params: {
            slug: item.slug
          }
        },
        image: item.image
      }
    }

    return {
      prepareData
    }
  }
}
</script>

<style lang="scss"></style>
