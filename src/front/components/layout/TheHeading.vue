<template>
  <header class="header">
    <div class="header-bg" />
    <div class="container pece-container z-20">
      <div class="relative flex py-2">
        <lazy-hydrate ssr-only>
          <navigation class="w-1/2 md:w-8/12 hidden md:block" />
        </lazy-hydrate>
        <menu-mobile v-slot="{ id, show }" class="w-1/3 p-2 pl-0 -ml-1 md:hidden">
          <navigation :id="id" :showMenuMobile="show" :mobile="true" />
        </menu-mobile>
        <div class="w-2/3 md:w-4/12 pt-2 flex justify-end">
          <search class="w-full" />
        </div>
      </div>
      <div class="flex flex-wrap pt-4 sm:py-8 sm:pl-4">
        <div class="w-full sm:w-1/2 text-center">
          <nuxt-link :to="{ name: `home___${$i18n.locale}` }">
            <img
              class="w-56 inline sm:block"
              src="~/assets/images/logo-pece.png"
              alt="Logo PECE project"
            >
          </nuxt-link>
        </div>
        <div class="w-full sm:w-1/2">
          <ul class="flex items-center justify-center sm:justify-end py-8">
            <li class="mr-8">
              <dark-theme />
            </li>
            <li class="mr-5">
              <button @click="onOpen" type="button">
                {{ $t('login') }}
              </button>
            </li>
            <li>
              <nuxt-link
                :to="{ name: `register___${$i18n.locale}` }"
                class="link-accent"
              >
                {{ $t('register') }}
              </nuxt-link>
            </li>
          </ul>
        </div>
      </div>
    </div>
    <transition name="fade">
      <Modal
        v-if="isOpen"
        @onClose="onClose"
      >
        <ModalHeader>
          Log In
        </ModalHeader>
        <ModalBody>
          <LoginForm />
        </ModalBody>
      </Modal>
    </transition>
  </header>
</template>

<script>
import { watch } from '@vue/composition-api'
import Navigation from '@/components/Navigation'
import Search from '@/components/Search'
import useDisclosure from '@/composable/useDisclosure'

export default {
  name: 'TheHeading',

  components: {
    Search,
    Navigation,
    LoginForm: () => import(/* webpackChunkName: "AuthLogin" */ '@/components/auth/Login'),
    MenuMobile: () => import(/* webpackChunkName: "MenuMobile" */ '@/components/MenuMobile'),
    DarkTheme: () => import(/* webpackChunkName: "DarkTheme" */ '@/components/DarkTheme')
  },

  setup (_, { isServer }) {
    const { isOpen, onOpen, onClose } = useDisclosure()

    watch('$route', () => {
      if (isOpen.value) {
        onClose()
      }
    })

    return {
      isOpen,
      onOpen,
      onClose
    }
  }
}
</script>

<style lang="scss">
.header-bg {
  @apply w-full h-56 z-10 absolute left-0 top-0 bg-center bg-no-repeat;
  background-image: url('~@/assets/images/bg-header.svg');

  @screen lg {
    @apply bg-top;
  }
}

.hamburguer {
  span {
    @apply bg-gray-900 block;
    width: 100%;
    height: 3px;
    &:not(last-child) {
      margin-bottom: 3px;
    }
  }
}
</style>
