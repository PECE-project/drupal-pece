<template>
  <div class="mt-20 mb-40 w-full lg:w-3/5 mx-auto">
    <h1 class="font-bold text-4xl leading-none">
      Create an account
    </h1>
    <RegisterForm />
  </div>
</template>

<script>
export default {
  name: 'Register',

  components: {
    RegisterForm: () => import(/* webpackChunkName: "AuthLogin" */ '@/components/auth/Register')
  }
}
</script>

<style lang="scss"></style>
