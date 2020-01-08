<template>
  <div class="user mt-6">
    <h1 class="font-bold text-4xl uppercase mb-6">
      {{ item.fullname }}
    </h1>
    <div class="flex flex-wrap lg:flex-no-wrap">
      <section class="user-content w-full morder-2 lg:order-1 lg:w-4/6">
        <h2>
          POSITION
        </h2>
        <p>
          Contributor
        </p>
        <h2>
          BIOGRAPHY
        </h2>
        <p>
          Animi accusamus quasi, sed quam accusantium. Rutrum commodo molestiae excepteur! Recusandae ea atque, optio fames commodi, neque ac sit diam? Eiusmod mauris at sunt diamlorem occaecati occaecati magnam lobortis aptent. Irure pede. Primis vulputate magna labore.
        </p>
      </section>
      <section class="user-sidebar w-full order-1 lg:order-2 mb-10 pr-0 lg:mt-0 lg:w-2/6 lg:pl-8 xl:pl-12">
        <div class="user-sidebar__avatar">
          <h2 class="user-sidebar__title font-bold mb-2">
            PICTURE
          </h2>
          <img v-if="item.image" :src="item.image.url" :alt="item.image.alt" class="w-full h-full object-cover">
        </div>
        <div class="user-sidebar__tags mt-6">
          <h2 class="user-sidebar__title font-bold mb-2">
            TAGS
          </h2>
          <ul class="flex mt-2">
            <li>
              <tag :data="fakeTag" />
            </li>
            <li>
              <tag :data="fakeTag" />
            </li>
          </ul>
        </div>
      </section>
    </div>
  </div>
</template>

<script>
import { users } from '@/utils/fake'

export default {
  name: 'User',
  components: {
    Tag: () => import(/** webpackChunkName: "Tag" */ '@/components/Tag')
  },
  setup (_, { root }) {
    const fakeTag = {
      label: 'Foo',
      to: {
        path: '/'
      }
    }

    return {
      fakeTag,
      item: users.find(item => item.slug === root.$route.params.slug)
    }
  }
}
</script>

<style lang="scss">
.user {
  h2 {
    @apply text-xl;
  }
}
.user-content {
  h2 {
    @apply font-bold;
  }
  p {
    @apply mt-2 mb-4
  }
}
</style>
