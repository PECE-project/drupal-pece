<template>
  <article class="card rounded overflow-hidden shadow-pece">
    <div class="card__media">
      <a href="#">
        <img src="~/assets/images/media/786-320x200.jpg" alt="Description image" class="w-full block">
      </a>
    </div>
    <div class="card__content p-3">
      <header class="card__header">
        <h2 class="card__title text-sm font-bold text-gray-900 leading-tight">
          <a href="#">
            Traces of future
          </a>
        </h2>
      </header>
      <footer class="card__meta mt-1">
        <div class="card__info text-gray-600">
          <a href="#" class="card__user-link">
            <span class="underline">Mike Fortun</span>
          </a>
          <span>•</span>
          <span class="card__post-date">2 day ago</span>
        </div>
        <div class="card__tags mt-4">
          <ul class="flex">
            <li v-for="tag in fakeTags" :key="tag.label">
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
    Tag: () => import(/* webpackChunkName: "Tag" */ '@/components/Tag')
  },
  props: {
    data: {
      type: Object,
      required: true
    }
  },
  setup () {
    const fakeTags = [
      {
        label: '#science',
        to: {
          path: '/'
        }
      },
      {
        label: '#climatology',
        to: {
          path: '/'
        }
      }
    ]

    return {
      fakeTags
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
