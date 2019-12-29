<template>
  <header class="header">
    <div class="header-bg" />
    <div class="container pece-container z-20">
      <div class="flex py-2">
        <navigation class="w-1/2 sm:w-8/12 hidden md:block" />
        <div class="w-8/12 p-4 md:hidden">
          MENU
        </div>
        <div class="w-1/2 sm:w-4/12 ">
          <search class="my-2" />
        </div>
      </div>
      <div class="flex flex-wrap pt-4 sm:py-8 sm:pl-4">
        <div class="w-full sm:w-1/2 text-center">
          <img
            class="w-56 inline sm:block"
            src="~/assets/images/logo-pece.png"
            alt="Logo PECE project"
          >
        </div>
        <div class="w-full sm:w-1/2">
          <ul class="flex justify-center sm:justify-end py-8">
            <li class="mr-5">
              <a href="/">
                {{ $t('login') }}
              </a>
            </li>
            <li>
              <a
                href="/"
                class="link-accent"
              >
                {{ $t('register') }}
              </a>
            </li>
          </ul>
        </div>
      </div>
    </div>
  </header>
</template>

<script>
import Navigation from '@/components/Navigation'
import Search from '@/components/Search'

export default {
  name: 'TheHeading',
  components: {
    Search,
    Navigation
  }
}
</script>

<style lang="scss">
.header-bg {
  @apply w-full h-56 z-10 absolute left-0 top-0 bg-top bg-no-repeat;
  background-image: url('~@/assets/images/bg-header.svg');
  display: none;

  @screen lg {
    display: block;
  }
}
</style>
