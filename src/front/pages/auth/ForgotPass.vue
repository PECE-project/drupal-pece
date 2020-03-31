<template>
  <div class="mt-20 mb-40 w-full lg:w-1/3 mx-auto">
    <h1 class="font-bold text-4xl leading-none">
      Forgot Password?
    </h1>
    <p id="email-help-text" class="text-md mt-2 text-gray-600">
      Enter your account email address and we will send you a link to reset your password.
    </p>
    <ForgotPassForm />
  </div>
</template>

<script>
export default {
  name: 'ForgotPass',

  components: {
    ForgotPassForm: () => import(/* webpackChunkName: "ForgotPassForm" */ '@/components/auth/ForgotPass')
  }
}
</script>

<style lang="scss"></style>
