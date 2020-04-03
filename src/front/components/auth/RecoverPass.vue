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
            There were some errors resetting your password
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
            New password created
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
        <FormInput
          id="password"
          v-model="reset.password"
          type="password"
          name="password"
          aria-describedby="password-help-text"
        />
        <FormErrorMessage :errors="errors" />
      </FormControlValidate>
      <FormControlValidate
        v-slot="{ errors }"
        rules="required|min:8|confirmed:password"
        name="Password confirm"
        class="mt-8"
      >
        <FormLabel
          for="password_confirm"
          class="pb-0"
        >
          Password confirm
        </FormLabel>
        <FormInput
          id="password_confirm"
          v-model="reset.password_confirm"
          type="password"
          name="password_confirm"
          aria-describedby="password-help-text"
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
import { ref, onMounted } from '@vue/composition-api'
import api from '@/services/api'

export default {
  name: 'RecoverPassForm',

  setup (_, { root }) {
    const serverErrors = ref([])

    const alertRecover = ref({
      show: false,
      type: 'info',
      message: 'Password changed successfully.'
    })

    const reset = ref({
      mail: null,
      password: null,
      password_confirm: null
    })

    onMounted(() => {
      setEmailRecover()
    })

    function setEmailRecover () {
      reset.value.mail = localStorage.getItem('mailRecoveryPass')
    }

    function submit (isValid) {
      serverErrors.value = []
      return api('/user/lost-password-reset?_format=json', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify({
          name: reset.value.mail,
          temp_pass: root.$route.params.token,
          new_pass: reset.value.pass
        })
      })
        .then((res) => {
          alertRecover.value.show = true
          alertRecover.value.message = res.message
          localStorage.removeItem('mailRecoveryPass')
        })
        .catch((e) => {
          serverErrors.value.push({
            message: e.message
          })
        })
    }

    return {
      submit,
      reset,
      serverErrors,
      alertRecover
    }
  }
}
</script>

<style lang="scss"></style>
