<template>
  <FormObserveValidate
    @submitted="submit"
    name="form-forgot-pass"
  >
    <template v-slot="{ invalid }">
      <div
        v-if="serverErrors.length"
        class="mt-6"
      >
        <Alert>
          <span slot="title">
            Some errors occurred when requesting password recovery
          </span>
          <ul slot="description" class="list-disc ml-4">
            <li v-for="(error, index) in serverErrors" :key="`server-error${index}`">
              {{ error.message }}
            </li>
          </ul>
        </Alert>
      </div>
      <div
        v-if="alertRecover.show"
        class="mt-6"
      >
        <Alert type="info">
          <span slot="title">
            Requested recovery
          </span>
          <span slot="description">
            {{ alertRecover.message }}
            <br><br>
            <nuxt-link :to="{ name: 'login' }">
              <strong>Go to login page</strong>
            </nuxt-link>
          </span>
        </Alert>
      </div>
      <FormControlValidate
        v-slot="{ errors }"
        rules="required|email"
        name="mail"
        class="mt-8"
      >
        <FormLabel
          for="username"
          class="pb-0"
        >
          Email
        </FormLabel>
        <!-- eslint-disable vue-a11y/no-autofocus -->
        <FormInput
          id="mail"
          v-model="mail"
          type="email"
          name="mail"
          autofocus
          aria-describedby="mail-help-text"
        />
        <FormErrorMessage :errors="errors" />
      </FormControlValidate>
      <button
        :disabled="invalid"
        :class="{ 'opacity-50': invalid }"
        type="submit"
        class="mt-8 btn-accent"
      >
        Request password reset
      </button>
    </template>
  </FormObserveValidate>
</template>

<script>
import { ref } from '@vue/composition-api'
import api from '@/services/api'

export default {
  name: 'ForgotPassForm',

  setup () {
    const serverErrors = ref([])
    const alertRecover = ref({
      show: false,
      message: 'If the email you specified exists in our system, we’ve sent you a password reset link'
    })
    const mail = ref(null)

    function setEmailStorage () {
      if (mail.value) { localStorage.setItem('mailRecoveryPass', mail.value) }
    }

    function submit (isValid) {
      setEmailStorage()
      serverErrors.value = []
      return api('/user/lost-password?_format=json', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({
          mail: mail.value
        })
      })
        .then((res) => {
          alertRecover.value.show = true
        })
        .catch((e) => {
          serverErrors.value.push({
            message: e.message
          })
        })
    }

    return {
      submit,
      mail,
      alertRecover,
      serverErrors
    }
  }
}
</script>

<style lang="scss"></style>
