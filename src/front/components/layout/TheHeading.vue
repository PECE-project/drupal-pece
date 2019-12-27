<template>
  <header class="header">
    <div class="header-bg" />
    <div class="container pece-container z-20">
      <div class="flex py-2">
        <navigation class="w-8/12 hidden md:block" />
        <div class="w-4/12 ">
          <search class="my-2" />
        </div>
      </div>
      <div class="flex py-8 pl-4">
        <div class="w-1/2">
          <img
            class="w-56"
            src="~/assets/images/logo-pece.png"
            alt="Logo PECE project"
          >
        </div>
        <div class="w-1/2">
          <ul class="flex justify-end py-8">
            <li class="mr-5">
              <a href="/">
                Log in
              </a>
            </li>
            <li>
              <a
                href="/"
                class="bg-accent rounded-full py-3 px-6 text-white hover:bg-accentHover"
              >
                Register
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

  @media (min-width: 768px) {
    display: block;
  }
}
</style>
