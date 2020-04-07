<template>
  <div class="mt-20 mb-40 w-full lg:w-1/3 mx-auto">
    <h1 class="font-bold text-4xl leading-none">
      Reset Password
    </h1>
    <p id="email-help-text" class="text-md mt-2 text-gray-700">
      Password must be at least 8 characters long and contain at least 6 unique characters.
    </p>
    <RecoverPassForm />
  </div>
</template>

<script>
export default {
  name: 'ResetPass',

  components: {
    RecoverPassForm: () => import(/* webpackChunkName: "RecoverPassForm" */ '@/components/auth/RecoverPass')
  }
}
</script>

<style lang="scss"></style>
