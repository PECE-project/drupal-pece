<template>
  <div class="menu-mobile">
    <button
      @click="toggleMenu"
      @keydown.enter="toggleMenu"
      :aria-expanded="show"
      aria-label="Main Menu"
      class="font-bold p-3 flex"
      aria-controls="menu-mobile"
    >
      <div :class="{ 'hamburguer--active': show }" class="hamburguer mt-1 mr-2 w-5">
        <span />
        <span />
        <span />
      </div>
      <span>MENU</span>
    </button>
    <transition name="slide">
      <slot id="menu-mobile" :show="show" v-if="show" />
    </transition>
  </div>
</template>

<script>
import { reactive, toRefs } from '@vue/composition-api'

export default {
  name: 'MenuMobile',
  setup () {
    const state = reactive({ show: false })

    function toggleMenu () {
      state.show = !state.show
    }

    return {
      ...toRefs(state),
      toggleMenu
    }
  }
}
</script>

<style lang="scss">
.hamburguer {
  transition: margin .5s ease;
  span {
    transform-origin: 0% 0%;
    transition: transform .5s cubic-bezier(0.77,0.2,0.05,1.0),
                background .5s cubic-bezier(0.77,0.2,0.05,1.0),
                opacity .55s ease;
  }
  &--active {
    margin-right: 0;
    margin-top: 5px;
    span {
      transform: rotate(45deg) translate(-2px, -1px);
    }
    span:nth-child(2) {
      @apply opacity-0;
      transform: rotate(0deg) scale(0.2, 0.2);
    }
    span:nth-child(3) {
      transform-origin: 0% 100%;
      transform: rotate(-45deg) translate(0, -1px);
    }
  }
}
</style>
