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
import { ref } from '@vue/composition-api'

export default {
  name: 'RecoverPassForm',

  setup () {
    const serverErrors = ref([])
    const reset = ref({
      password: null,
      password_confirm: null
    })

    function submit (isValid) {
      console.log('submetido', isValid)
    }

    return {
      submit,
      reset,
      serverErrors
    }
  }
}
</script>

<style lang="scss"></style>
