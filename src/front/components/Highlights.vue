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
          class="highlights__list__item w-full cursor-pointer"
        >
          <button
            ref="highlightItem"
            :class="{ 'highlights__list__item__button--active': hl.title === highlight.title }"
            @click="setChosenHighlight(hl)"
            @keydown.enter="setChosenHighlight(hl)"
            @keydown="navBetweenTabsByArrows($event, index)"
            class="highlights__list__item__button h-full w-full block p-5 text-left"
            data-pece="highlights-items"
          >
            <h2 class="text-gray-800 text-sm mb-1 leading-tight">
              {{ hl.title }}
            </h2>
            <span class="text-gray-600 text-xs">{{ hl.created_at }}</span>
          </button>
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
  setup (_, { root, refs }) {
    const state = reactive({
      highlight: highlights[0],
      highlights
    })

    function setChosenHighlight (hl) {
      state.highlight = { ...hl }
      refs.highlightCover.focus()
    }

    function navBetweenTabsByArrows ($e, index) {
      const i = {
        ArrowRight: index + 1,
        ArrowLeft: index - 1,
        Home: 0,
        End: state.highlights.length - 1
      }
      if (state.highlights[i[$e.key]]) {
        state.highlight = { ...state.highlights[i[$e.key]] }
        refs.highlightItem[i[$e.key]].focus()
      }
    }

    return {
      ...toRefs(state),
      setChosenHighlight,
      navBetweenTabsByArrows
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
    &__item__button {
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
