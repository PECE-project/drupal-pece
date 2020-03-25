<template>
  <div class="modal fixed w-full h-full z-40">
    <div
      v-show="overlay"
      @click="!persistent && $emit('onClose')"
      @keyup.enter="!persistent && $emit('onClose')"
      class="z-20 w-full h-full top-0 left-0 fixed bg-overlay"
    />
    <section
      :aria-describedby="`modal-${_uid}-body`"
      :aria-labelledby="`modal-${_uid}-header`"
      :style="{ 'max-width': '28rem' }"
      role="dialog"
      aria-modal="true"
      tabindex="-1"
      class="modal modal__content z-30 bg-white w-full fixed p-6 rounded"
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
    },
    scrollable: {
      type: Boolean,
      default: false
    },
    persistent: {
      type: Boolean,
      default: false
    }
  },

  setup ({ scrollable }, { emit }) {
    provide('onClose', onClose)

    function onClose () {
      emit('onClose')
    }

    function escFullScreen (e) {
      if (e.key === 'Escape') {
        onClose()
      }
    }

    function toggleOverflow (overflow) {
      if (scrollable) { return }
      document.body.style.overflow = overflow
    }

    onMounted(() => {
      window.addEventListener('keydown', escFullScreen, true)
      toggleOverflow('hidden')
    })

    onUnmounted(() => {
      window.removeEventListener('keydown', escFullScreen, true)
      toggleOverflow('auto')
    })
  }
}
</script>

<style lang="scss">
.modal {
  &__content {
    top: 15%;
    left: 50%;
    transform: translateX(-50%);
  }
}
</style>
