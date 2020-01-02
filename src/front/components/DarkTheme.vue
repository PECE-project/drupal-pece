<template>
  <button
    @click="toggleDarkTheme"
    @keydown.enter="toggleDarkTheme"
    class="p-2"
  >
    <svg-icon
      :title="$t('a11y.dark_theme_title_on')"
      v-if="darkTheme"
      class="text-gray-600 fill-current"
      width="20px"
      height="20px"
      name="day"
      fill="#fff"
    />
    <svg-icon
      :title="$t('a11y.dark_theme_title_off')"
      v-else
      class="text-gray-600 fill-current"
      width="20px"
      height="20px"
      name="night"
    />
    <style :media="darkTheme ? 'screen' : 'none'">
      html {
      background-color: #222 !important;
      }

      body {
      filter: contrast(90%) invert(90%) hue-rotate(180deg) !important;
      -ms-filter: invert(100%);
      -webkit-filter: contrast(90%) invert(90%) hue-rotate(180deg) !important;
      text-rendering: optimizeSpeed;
      image-rendering: optimizeSpeed;
      -webkit-font-smoothing: antialiased;
      -webkit-image-rendering: optimizeSpeed;
      }

      input, textarea, select {
      color: purple;
      }

      img, video, iframe, canvas, svg, embed[type='application/x-shockwave-flash'], object[type='application/x-shockwave-flash'], *[style*='url('] {
      filter: invert(100%) hue-rotate(-180deg) !important;
      -ms-filter: invert(100%) !important;
      -webkit-filter: invert(100%) hue-rotate(-180deg) !important;
      }
    </style>
  </button>
</template>

<script>
import { reactive, toRefs, onMounted } from '@vue/composition-api'

export default {
  name: 'DarkTheme',
  setup () {
    const state = reactive({ darkTheme: false })

    onMounted(() => {
      state.darkTheme = window.getComputedStyle(document.documentElement).getPropertyValue('content') === 'dark' ||
        !!localStorage.getItem('darkTheme') ||
        false
    })

    function toggleDarkTheme () {
      state.darkTheme = !state.darkTheme
      if (state.darkTheme) {
        return localStorage.setItem('darkTheme', 'on')
      }
      localStorage.removeItem('darkTheme')
    }

    return {
      ...toRefs(state),
      toggleDarkTheme
    }
  }
}
</script>

<style lang="scss"></style>
