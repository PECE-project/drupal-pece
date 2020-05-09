<template>
  <FormObserveValidate
    @submitted="submit"
    name="form-login"
    data-nw="form-login"
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
        rules="required|email"
        name="email"
        class="mt-8"
      >
        <FormLabel
          for="email"
          class="pb-0"
        >
          Email
        </FormLabel>
        <FormHelperText
          id="email-help-text"
          class="mb-1"
        >
          Enter your PECE Drupal Distro Email.
        </FormHelperText>
        <!-- eslint-disable vue-a11y/no-autofocus -->
        <FormInput
          id="email"
          v-model="auth.username"
          type="text"
          name="email"
          data-nw="email"
          autofocus
          aria-describedby="email-help-text"
        />
        <FormErrorMessage :errors="errors" />
        <p class="text-xs mt-2">
          If you don't have an user,
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
          Enter the password that accompanies your email.
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

      <p class="mt-8">
        <recaptcha
          ref="recaptcha"
          v-if="hasCaptcha"
          :key="recaptcha.size"
          :size="recaptcha.size"
          :loadRecaptchaScript="true"
          @verify="recaptchaSuccess"
          @error="recaptchaError"
          :sitekey="recaptcha.challenged ? recaptcha.siteKeyV2 : recaptcha.siteKeyV3"
          data-nw="recaptcha"
        />
      </p>

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
import { ref, computed } from '@vue/composition-api'

export default {
  name: 'LoginForm',

  components: {
    recaptcha: () => import('vue-recaptcha')
  },

  setup (_, { root, refs }) {
    const hasCaptcha = process.env.NUXT_RECAPTCHA_SITE_KEY_V2
    const serverErrors = ref([])

    const recaptcha = computed(() => root.$store.getters['user/recaptcha'])

    const auth = ref({
      username: null,
      password: null
    })

    async function submit (isValid) {
      resetErrors()
      if (!isValid) { return serverErrors.value.push({ message: 'Invalid form' }) }
      if (!recaptcha.value.success && recaptcha.value.size === 'normal') {
        return handlerError({ message: 'Resolve reCAPTCHA' })
      }
      if (recaptcha.value.success || !hasCaptcha) { return login() }
      await refs.recaptcha.execute()
    }

    async function login () {
      try {
        await root.$store.dispatch('user/login', auth.value)
        window.location.href = root.$route.query.redirect || '/'
      } catch (e) {
        handlerError(e)
        if (e.message.includes('attempts')) {
          root.$store.dispatch('user/reCaptchaError')
        }
      }
    }

    async function recaptchaSuccess (response) {
      if (!recaptcha.value.challenged) {
        await root.$store.dispatch('user/checkScoreReCaptcha', response)
        return login()
      }
      root.$store.dispatch('user/reCaptchaSuccess')
    }

    function recaptchaError (e) {
      handlerError(e)
      root.$store.dispatch('user/reCaptchaError')
    }

    function resetErrors () {
      serverErrors.value = []
    }

    function handlerError (e) {
      console.log(e)
      serverErrors.value.push({
        message: e.message
      })
    }

    return {
      auth,
      hasCaptcha,
      login,
      recaptcha,
      recaptchaError,
      recaptchaSuccess,
      serverErrors,
      submit
    }
  }
}
</script>

<style lang="scss"></style>
