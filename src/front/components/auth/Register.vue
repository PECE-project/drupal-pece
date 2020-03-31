<template>
  <FormObserveValidate
    @submitted="register"
    name="form-register"
  >
    <template v-slot="{ invalid }">
      <div
        v-if="serverErrors.length"
        class="mt-6"
      >
        <Alert>
          <span slot="title">
            Some errors occurred while registering
          </span>
          <ul slot="description" class="list-disc ml-4">
            <li v-for="(error, index) in serverErrors" :key="`server-error${index}`">
              {{ error.message }}
            </li>
          </ul>
        </Alert>
      </div>
      <section class="mt-8">
        <h3 class="text-2xl rounded py-2 px-3 bg-accent text-white">
          User information
        </h3>
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
          <!-- eslint-disable vue-a11y/no-autofocus -->
          <FormInput
            id="username"
            v-model="username"
            type="text"
            name="username"
            autofocus
            aria-describedby="username-help-text"
          />
          <FormErrorMessage :errors="errors" />
          <p id="username-help-text" class="text-xs mt-2">
            Spaces are allowed; punctuation is not allowed except for periods, hyphens, apostrophes, and underscores.
          </p>
        </FormControlValidate>
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
          <FormInput
            id="email"
            v-model="mail"
            type="email"
            name="email"
            aria-describedby="email-help-text"
          />
          <FormErrorMessage :errors="errors" />
        </FormControlValidate>
        <p id="email-help-text" class="text-xs mt-2">
          A valid e-mail address. All e-mails from the system will be sent to this address. The e-mail address is not made public and will only be used if you wish to receive a new password or wish to receive certain news or notifications by e-mail.
        </p>
        <FormControl class="mt-8">
          <FormLabel
            for="zotero"
            class="pb-0"
          >
            Zotero username
          </FormLabel>
          <FormInput
            id="zotero"
            v-model="zotero"
            type="text"
            name="zotero"
            aria-describedby="zotero-help-text"
          />
        </FormControl>
        <p id="zotero-help-text" class="text-xs mt-2">
          This field will be used to map authorship for the bibliography imported from the Zotero platform.
        </p>
      </section>
      <div class="my-12">
        <Divider />
      </div>
      <section>
        <h3 class="text-2xl rounded py-2 px-3 bg-accent text-white">
          Profile
        </h3>
        <FormControl class="mt-8">
          <FormLabel
            for="fullname"
            class="pb-0"
          >
            Full name
          </FormLabel>
          <FormInput
            id="fullname"
            v-model="profile.fullname"
            type="text"
            name="fullname"
          />
        </FormControl>
        <FormControl class="mt-8">
          <FormLabel
            for="institution"
            class="pb-0"
          >
            Institution
          </FormLabel>
          <FormInput
            id="institution"
            v-model="profile.institution"
            type="text"
            name="institution"
          />
        </FormControl>
        <FormControl class="mt-8">
          <FormLabel
            for="position"
            class="pb-0"
          >
            Position
          </FormLabel>
          <FormInput
            id="position"
            v-model="profile.position"
            type="text"
            name="position"
          />
        </FormControl>
        <FormControl class="mt-8">
          <FormLabel
            for="biography"
            class="pb-0"
          >
            Biography
          </FormLabel>
          <FormTextarea
            id="biography"
            v-model="profile.biography"
            rows="5"
            type="text"
            name="biography"
          />
        </FormControl>
        <FormControl class="mt-8">
          <FormLabel
            for="openpgp"
            class="pb-0"
          >
            OpenPGP key
          </FormLabel>
          <FormUpload
            id="openpgp"
            type="file"
            accept=".pub"
            aria-describedby="openpgp-help-text"
          />
        </FormControl>
        <p id="openpgp-help-text" class="text-xs mt-2">
          Files must be less than <strong>100 MB</strong>. <br>
          Allowed file types: <strong>pub</strong>.
        </p>
      </section>
      <div class="my-12">
        <Divider />
      </div>
      <section>
        <h3 class="text-2xl rounded py-2 px-3 bg-accent text-white">
          Location
        </h3>
        <FormControl class="mt-8">
          <FormLabel
            for="street"
            class="pb-0"
          >
            Street
          </FormLabel>
          <FormInput
            id="street"
            v-model="location.street"
            rows="5"
            type="text"
            name="street"
          />
        </FormControl>
        <FormControl class="mt-8">
          <FormLabel
            for="additional"
            class="pb-0"
          >
            Additional
          </FormLabel>
          <FormInput
            id="additional"
            v-model="location.additional"
            rows="5"
            type="text"
            name="additional"
          />
        </FormControl>
        <FormControl class="mt-8">
          <FormLabel
            for="city"
            class="pb-0"
          >
            City
          </FormLabel>
          <FormInput
            id="city"
            v-model="location.city"
            rows="5"
            type="text"
            name="city"
          />
        </FormControl>
        <FormControl class="mt-8">
          <FormLabel
            for="state"
            class="pb-0"
          >
            State/Province
          </FormLabel>
          <FormInput
            id="state"
            v-model="location.state"
            rows="5"
            type="text"
            name="state"
          />
        </FormControl>
        <FormControl class="mt-8">
          <FormLabel
            for="zipcode"
            class="pb-0"
          >
            Postal code
          </FormLabel>
          <FormInput
            id="zipcode"
            v-model="location.zipcode"
            type="text"
            inputmode="numeric"
            name="zipcode"
          />
        </FormControl>
        <FormControl class="mt-8">
          <FormLabel
            for="country"
            class="pb-0"
          >
            Country
          </FormLabel>
          <FormSelect
            id="country"
            v-model="location.country"
            name="country"
            placeholder="Select option"
          >
            <option v-for="country in countries" :key="`country${country.id}`" :value="country.name">
              {{ country.name }}
            </option>
          </FormSelect>
        </FormControl>
        <FormControl class="mt-8">
          <FormLabel
            for="location-name"
            class="pb-0"
          >
            Location name
          </FormLabel>
          <FormInput
            id="location-name"
            v-model="location.name"
            rows="5"
            type="text"
            name="location-name"
            aria-describedby="location-name-help-text"
          />
        </FormControl>
        <p id="location-name-help-text" class="text-xs mt-2">
          e.g. a place of business, venue, meeting point
        </p>
      </section>
      <div class="my-12">
        <Divider />
      </div>
      <button
        :disabled="invalid"
        :class="{ 'opacity-50': invalid }"
        type="submit"
        class="btn-accent"
      >
        Create new account
      </button>
    </template>
  </FormObserveValidate>
</template>

<script>
import { ref, reactive, toRefs } from '@vue/composition-api'

export default {
  name: 'RegisterForm',

  setup () {
    const serverErrors = ref([])
    const countries = [
      {
        id: 1,
        name: 'Brazil'
      },
      {
        id: 2,
        name: 'EUA'
      }
    ]

    const state = reactive({
      username: null,
      mail: null,
      zotero: null,
      profile: {
        fullname: null,
        institution: null,
        position: null,
        biography: null,
        openpgp: null
      },
      location: {
        name: null,
        street: null,
        additional: null,
        city: null,
        state: null,
        zipcode: null,
        country: null
      }
    })

    function register (isValid) {
      console.log('submetido', isValid)
    }

    return {
      ...toRefs(state),
      serverErrors,
      countries,
      register
    }
  }
}
</script>

<style lang="scss">
</style>
