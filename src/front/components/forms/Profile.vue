<template>
  <div>
    <FormControl class="mt-8">
      <FormLabel
        for="fullname"
        class="pb-0"
      >
        Full name
      </FormLabel>
      <FormInput
        id="fullname"
        :value="value.fullname"
        @input="val => { value.fullname = val }"
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
        :value="value.institution"
        @input="val => { value.institution = val }"
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
        :value="value.position"
        @input="val => { value.position = val }"
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
        :value="value.biography"
        @input="val => { value.biography = val }"
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
  </div>
</template>

<script>
export default {
  name: 'ProfileForm',

  props: {
    value: {
      type: Object,
      required: true
    }
  }
}
</script>

<style lang="scss"></style>
