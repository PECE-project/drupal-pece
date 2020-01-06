<template>
  <div v-if="users.length" class="list-users">
    <list-cards :data="users" :vertical="true">
      <template v-slot="{ item }">
        <horizontal-card :data="item" />
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
  }
}
</script>

<style lang="scss"></style>
