<template>
  <FormObserveValidate
    @submitted="login"
    name="form-login"
  >
    <template v-slot="{ invalid }">
      <div
        v-if="serverErrors.length"
        class="mt-6"
      >
        <Alert>
          <span slot="title">
            There were some login errors
          </span>
          <ul slot="description" class="list-disc ml-4">
            <li v-for="(error, index) in serverErrors" :key="`server-error${index}`">
              {{ error.message }}
            </li>
          </ul>
        </Alert>
      </div>
      <FormControlValidate
        v-slot="{ errors }"
        rules="required"
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
          data-nw="username"
          autofocus
          aria-describedby="username-help-text"
        />
        <FormErrorMessage :errors="errors" />
        <p class="text-xs mt-2">
          If you don't have an username,
          <nuxt-link
            :to="{ name: `register___${$i18n.locale}` }"
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
          data-nw="password"
          aria-describedby="password-help-text"
        />
        <FormErrorMessage :errors="errors" />
        <p class="text-xs mt-2">
          If you forgot your password,
          <nuxt-link
            :to="{ name: `forget-password___${$i18n.locale}`}"
            class="link-accent-inline"
            data-nw="link-forgot-pass"
          >
            request a new password.
          </nuxt-link>
        </p>
      </FormControlValidate>
      <button
        :disabled="invalid"
        :class="{ 'opacity-50': invalid }"
        type="submit"
        data-nw="btn-submit"
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

  setup (_, { root }) {
    const serverErrors = ref([])
    const auth = ref({
      username: null,
      password: null
    })

    async function login (isValid) {
      if (!isValid) { return serverErrors.value.push({ message: 'Invalid form' }) }
      serverErrors.value = []
      try {
        await root.$store.dispatch('user/login', auth.value)
        window.location.href = root.$route.query.redirect || '/'
      } catch (e) {
        serverErrors.value.push({
          message: e.message
        })
      }
    }

    return {
      auth,
      login,
      serverErrors
    }
  }
}
</script>

<style lang="scss"></style>
