<template>
  <div class="flex justify-center fixed w-full h-full z-40">
    <div
      v-show="overlay"
      @click="$emit('onClose')"
      @keyup.enter="$emit('onClose')"
      class="z-20 w-full h-full top-0 left-0 fixed bg-overlay"
    />
    <section
      :aria-describedby="`modal-${_uid}-body`"
      :aria-labelledby="`modal-${_uid}-header`"
      role="dialog"
      aria-modal="true"
      tabindex="-1"
      class="z-30 bg-white w-11/12 md:w-2/5 fixed p-6 rounded"
    >
      <FocusLock>
        <slot />
      </FocusLock>
    </section>
  </div>
</template>

<script>
import { provide, onMounted, onUnmounted } from '@vue/composition-api'

export default {
  name: 'Modal',

  components: {
    FocusLock: () => import('vue-focus-lock')
  },

  provide () {
    return {
      key: `modal-${this._uid}`
    }
  },

  props: {
    overlay: {
      type: Boolean,
      default: true
    }
  },

  setup (_, { emit }) {
    provide('onClose', onClose)

    function onClose () {
      emit('onClose')
    }

    function escFullScreen (e) {
      if (e.key === 'Escape') {
        onClose()
      }
    }

    onMounted(() => {
      window.addEventListener('keydown', escFullScreen, true)
    })

    onUnmounted(() => {
      window.removeEventListener('keydown', escFullScreen, true)
    })
  }
}
</script>

<style lang="scss"></style>
