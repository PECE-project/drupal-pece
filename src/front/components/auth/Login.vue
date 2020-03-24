<template>
  <FormObserveValidate @submitted="login" name="form-login">
    <FormControlValidate rules="required|email" class="mt-8">
      <FormLabel for="username" class="pb-0">
        Username
      </FormLabel>
      <FormHelperText id="username-help-text" class="m-0 text-xs mb-1">
        Enter your PECE Drupal Distro username.
      </FormHelperText>
      <FormInput id="username" v-model="auth.username" type="text" aria-describedby="username-help-text" />
    </FormControlValidate>
    <p class="text-xs mt-2">
      If you don't have an username,
      <nuxt-link to="register" class="link-accent-inline">
        create an account.
      </nuxt-link>
    </p>
    <FormControlValidate rules="required|min:8" class="mt-8">
      <FormLabel for="password" class="pb-0">
        Password
      </FormLabel>
      <FormHelperText id="password-help-text" class="m-0 text-xs mb-1">
        Enter the password that accompanies your username.
      </FormHelperText>
      <FormInput id="password" v-model="auth.password" type="password" aria-describedby="password-help-text" />
    </FormControlValidate>
    <p class="text-xs mt-2">
      If you forgot your password,
      <nuxt-link to="reset-password" class="link-accent-inline">
        request a new password.
      </nuxt-link>
    </p>
    <button class="bg-accent text-white mt-8">
      Log In
    </button>
  </FormObserveValidate>
</template>

<script>
import { ref } from '@vue/composition-api'

export default {
  name: 'LoginForm',

  setup () {
    const auth = ref({
      username: null,
      password: null
    })

    function login (isValid) {
      console.log('submetido', isValid)
    }

    return {
      auth,
      login
    }
  }
}
</script>

<style lang="scss"></style>
