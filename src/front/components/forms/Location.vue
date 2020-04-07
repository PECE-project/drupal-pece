<template>
  <div>
    <FormControl class="mt-8">
      <FormLabel
        for="street"
        class="pb-0"
      >
        Street
      </FormLabel>
      <FormInput
        id="street"
        :value="value.street"
        @input="val => { value.street = val }"
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
        :value="value.additional"
        @input="val => { value.additional = val }"
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
        :value="value.city"
        @input="val => { value.city = val }"
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
        :value="value.state"
        @input="val => { value.state = val }"
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
        :value="value.zipcode"
        @input="val => { value.zipcode = val }"
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
        :value="value.country"
        @change="val => { value.country = val }"
        name="country"
        placeholder="Select option"
      >
        <option
          v-for="country in countries"
          :key="`country${country.id}`"
          :value="country.name"
        >
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
        :value="value.name"
        @change="val => { value.name = val }"
        rows="5"
        type="text"
        name="location-name"
        aria-describedby="location-name-help-text"
      />
    </FormControl>
    <p id="location-name-help-text" class="text-xs mt-2">
      e.g. a place of business, venue, meeting point
    </p>
  </div>
</template>

<script>
export default {
  name: 'LocationForm',

  props: {
    value: {
      type: Object,
      required: true
    }
  }
}
</script>

<style lang="scss"></style>
