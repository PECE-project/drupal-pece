<template>
  <FormObserveValidate
    @submitted="login"
    name="form-login"
  >
    <template v-slot="{ invalid }">
      <FormControlValidate
        v-slot="{ errors }"
        rules="required|email"
        name="username"
        class="mt-8"
      >
        <FormLabel
          for="username"
          class="pb-0"
        >
          Username
        </FormLabel>
        <FormHelperText
          id="username-help-text"
          class="mb-1"
        >
          Enter your PECE Drupal Distro username.
        </FormHelperText>
        <!-- eslint-disable vue-a11y/no-autofocus -->
        <FormInput
          id="username"
          v-model="auth.username"
          type="text"
          name="username"
          autofocus
          aria-describedby="username-help-text"
        />
        <FormErrorMessage :errors="errors" />
        <p class="text-xs mt-2">
          If you don't have an username,
          <nuxt-link
            to="register"
            class="link-accent-inline"
          >
            create an account.
          </nuxt-link>
        </p>
      </FormControlValidate>
      <FormControlValidate
        v-slot="{ errors }"
        rules="required|min:8"
        name="password"
        class="mt-8"
      >
        <FormLabel
          for="password"
          class="pb-0"
        >
          Password
        </FormLabel>
        <FormHelperText
          id="password-help-text"
          class="m-0 text-xs mb-1"
        >
          Enter the password that accompanies your username.
        </FormHelperText>
        <FormInput
          id="password"
          v-model="auth.password"
          type="password"
          name="password"
          aria-describedby="password-help-text"
        />
        <FormErrorMessage :errors="errors" />
        <p class="text-xs mt-2">
          If you forgot your password,
          <nuxt-link
            to="reset-password"
            class="link-accent-inline"
          >
            request a new password.
          </nuxt-link>
        </p>
      </FormControlValidate>
      <button
        :disabled="invalid"
        :class="{ 'opacity-50': invalid }"
        type="submit"
        class="mt-8 btn-accent"
      >
        Log In
      </button>
    </template>
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
