<template>
  <div class="tabs">
    <ul
      ref="tabsList"
      v-show="tabList.length"
      class="tabs__list flex flex-wrap sm:flex-no-wrap border-b border-gray-300"
      role="tablist"
    >
      <li
        v-for="(tab, index) in tabList"
        :key="`tab${tab.uid}`"
        role="presentation"
        class="tabs__item w-1/2 sm:w-auto"
      >
        <a
          ref="tabsLinks"
          :id="`tab_${tab.uid}`"
          :class="{ 'uppercase': uppercase, 'tabs__link--disabled': tab.disabled }"
          :href="`#tab_section${tab.uid}`"
          @click.prevent="changeTab($event, index, tab)"
          @keydown.enter="changeTab($event, index, tab)"
          @keydown="navBetweenTabsByKeyBoard($event, index, tab)"
          :aria-selected="index === selectedIndex"
          :tabindex="index !== selectedIndex ? -1 : null"
          role="tab"
          class="tabs__link flex p-4 px-3 sm:px-6 block"
        >
          {{ tab.title }}
        </a>
      </li>
    </ul>
    <slot />
  </div>
</template>

<script>
import { reactive, toRefs, onMounted } from '@vue/composition-api'

export default {
  name: 'Tabs',
  props: {
    uppercase: {
      type: Boolean,
      default: false
    },
    defaultIndex: {
      default: 0,
      type: Number
    }
  },
  setup (props, { root, slots, refs }) {
    const state = reactive({
      selectedIndex: props.defaultIndex,
      tabList: []
    })

    function changeTab (e, index, tab) {
      if (tab.disabled) { return }
      const currentTab = refs.tabsList.querySelector('[aria-selected]')
      if (currentTab !== e.currentTarget) {
        state.selectedIndex = index
        updateTabs(currentTab, e.currentTarget)
        tab.el.hidden = false
      }
    }

    function updateTabs (currentTab, currentTarget) {
      currentTarget.focus()
      state.tabList.forEach((item) => {
        item.el.hidden = true
      })
    }

    function navBetweenTabsByKeyBoard (e, index, tab) {
      const i = {
        ArrowRight: index + 1,
        ArrowLeft: index - 1,
        Home: 0,
        End: state.tabList.length - 1
      }
      if (state.tabList[i[e.key]]) {
        e.preventDefault()
        const currentTab = refs.tabsList.querySelector('[aria-selected]')
        state.selectedIndex = i[e.key]
        updateTabs(currentTab, refs.tabsLinks[i[e.key]])
        state.tabList[i[e.key]].el.hidden = false
      }
    }

    function setAttrs (index) {
      state.tabList.forEach((item) => {
        item.el.setAttribute('id', `tab_section${item.uid}`)
        item.el.setAttribute('aria-labelledby', `tab_${item.uid}`)
      })
      state.tabList[0].el.hidden = false
    }

    onMounted(() => {
      const slotsTabs = slots.default() || []
      slotsTabs.forEach((child, index) => {
        if (child.tag) {
          const { title, disabled } = child.componentOptions.propsData
          const { _uid: uid, $el: el } = child.componentInstance
          state.tabList = [ ...state.tabList, {
            el,
            uid,
            title,
            disabled: disabled || false
          }]
          setAttrs()
        }
      })
    })

    return {
      ...toRefs(state),
      changeTab,
      navBetweenTabsByKeyBoard
    }
  }
}
</script>

<style lang="scss">
.tabs {
  &__item {
    &:first-child {
      .tabs__link {
        @apply pl-0;

        &[aria-selected="true"] {
          @apply border-l-0;
        }
      }
    }
  }
  &__link {
    @apply font-bold text-sm;
    &:before {
      @apply relative bg-gray-100 mr-2;
      content: '';
      width: 4px;
      height: 15px;
      top: 4px;
    }
    &[aria-selected="true"] {
      @apply relative border-l border-r border-gray-300;
      &:before {
        @apply bg-accent;
      }
      &:after {
        @apply absolute w-full left-0 bg-white;
        content: '';
        height: 1px;
        bottom: -1px;
      }
    }
    &--disabled {
      @apply opacity-50 cursor-not-allowed;
    }
  }
}
</style>
