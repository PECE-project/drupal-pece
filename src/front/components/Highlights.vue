<template>
  <div class="highlights shadow-pece">
    <h2 class="sr-only">
      Highligths of website
    </h2>
    <a
      ref="highlightCover"
      v-if="highlight.title"
      :href="highlight.link"
      :title="`${$t('see')} ${highlight.title}`"
      class="highlights__cover w-full block"
      data-pece="highlights-cover"
    >
      <picture v-if="highlight.images">
        <source :srcset="highlight.images.thumbnail" media="(max-width: 480px)">
        <source :srcset="highlight.images.medium" media="(max-width: 640px)">
        <img
          :src="highlight.images.large"
          :alt="highlight.images.alt"
          class="w-full highlights__cover__image"
        >
      </picture>
    </a>
    <nav>
      <ul class="highlights__list flex flex-wrap md:flex-no-wrap">
        <li
          v-for="(hl, index) in highlights"
          :key="`highlight-${index}`"
          :class="{ 'highlights__list__item--active': hl.title === highlight.title }"
          @click="setChosenHighlight(hl)"
          @keypress.enter="setChosenHighlight(hl)"
          :data-test="index"
          class="highlights__list__item p-4 w-full cursor-pointer"
          data-pece="highlights-items"
          tabindex="0"
        >
          <h2 class="text-gray-800 text-sm mb-1 leading-tight">
            {{ hl.title }}
          </h2>
          <span class="text-gray-600 text-xs">{{ hl.created_at }}</span>
        </li>
      </ul>
    </nav>
  </div>
</template>

<script>
import { reactive, toRefs } from '@vue/composition-api'

import { highlights } from '@/utils/fake'

export default {
  name: 'Highlights',
  setup (_, { refs }) {
    const state = reactive({ highlight: highlights[0] })

    function setChosenHighlight (hl) {
      state.highlight = { ...hl }
      refs.highlightCover.focus()
    }

    return {
      ...toRefs(state),
      highlights,
      setChosenHighlight
    }
  }
}
</script>

<style lang="scss">
.highlights {
  &__cover {
    @apply overflow-hidden bg-gray-100;
    min-height: auto;
    @screen md {
      min-height: 200px;
    }
    &:hover {
      .highlights__cover__image {
        transform: scale(1.05, 1.05);
      }
    }
    &__image {
      transition: transform.5s;
    }
  }
  &__list {
    &__item {
      @apply relative border-b border-solid border-gray-100;
      &--active, &:hover {
        @apply bg-gray-100;
      }
      &--active {
        &:before {
          @apply absolute left-0 w-full;
          content: '';
          background-color: inherit;
          top: -20px;
          height: 0;
        }
        @screen lg {
          &:before {
            height: 20px;
          }
        }
      }
      &:not(:last-child) {
        @screen md {
          @apply border-r;
        }
      }
    }
  }
}
</style>
