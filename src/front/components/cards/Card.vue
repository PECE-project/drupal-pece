<template>
  <article class="card rounded overflow-hidden shadow-pece">
    <div class="card__media">
      <nuxt-link :to="data.to">
        <img
          :src="data.image.url"
          :alt="data.image.alt"
          class="w-full block contains"
          style="height: 140px;"
        >
      </nuxt-link>
    </div>
    <div class="card__content p-3">
      <header class="card__header">
        <h2 class="card__title text-sm font-bold text-gray-900 leading-tight">
          <nuxt-link :to="data.to">
            {{ data.title }}
          </nuxt-link>
        </h2>
      </header>
      <footer class="card__meta mt-1">
        <div class="card__info text-gray-600">
          <nuxt-link
            :to="data.author.to"
            class="card__user-link"
          >
            <span class="underline">
              {{ data.author.name }}
            </span>
          </nuxt-link>
          <br>
          <span class="card__post-date">
            <TimeAgo
              :date="data.created"
              :locale="$i18n.locale"
            >
              <time
                :datetime="data.created"
                slot-scope="{ time }"
                class="card-timeago"
              >
                {{ time }}
              </time>
            </TimeAgo>
          </span>
        </div>
        <div class="card__tags mt-4">
          <ul v-if="data.tags.length" class="flex">
            <li v-for="tag in data.tags" :key="tag.id">
              <tag :data="tag" />
            </li>
          </ul>
        </div>
      </footer>
    </div>
  </article>
</template>

<script>

export default {
  name: 'Card',
  components: {
    TimeAgo: () => import(/* webpackChunkName: "TimeAgo" */ '@/components/time/Provider'),
    Tag: () => import(/* webpackChunkName: "Tag" */ '@/components/Tag')
  },
  props: {
    data: {
      type: Object,
      required: true
    }
  }
}
</script>

<style lang="scss">
.card {
  &__info {
    font-size: 12px;
  }
  &__tags {
    a {
      font-size: 10px;
    }
  }
}
</style>
