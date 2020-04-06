<template>
  <div class="mt-20 mb-40 w-full lg:w-1/3 mx-auto">
    <h1 class="font-bold text-4xl">
      PECE Log In
    </h1>
    <LoginForm />
  </div>
</template>

<script>
export default {
  name: 'Login',

  components: {
    LoginForm: () => import(/* webpackChunkName: "AuthLogin" */ '@/components/auth/Login')
  },

  head () {
    return {
      title: 'Login | PECE Project'
    }
  }
}
</script>

<style lang="scss"></style>
