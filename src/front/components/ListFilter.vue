<template>
  <div class="mt-4">
    <h3 aria-label="Filter by type" class="font-bold text-xl">
      Filter by:
    </h3>
    <ul class="mt-3">
      <li v-for="(item, index) in items" :key="`filter_${index}`" class="mb-1">
        <base-checkbox
          :id="`checkbox_filter_${index}`"
          :label="item.label"
          v-model="filter"
        />
      </li>
    </ul>
  </div>
</template>

<script>
import { reactive, toRefs } from '@vue/composition-api'

export default {
  name: 'ListFilter',
  props: {
    items: {
      type: Array,
      required: true
    }
  },
  setup (_, { emit }) {
    const state = reactive({
      filter: []
    })

    return {
      ...toRefs(state)
    }
  }
}
</script>

<style lang="scss"></style>
