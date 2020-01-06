import { shallowMount } from '@vue/test-utils'

import FilterList from '@/components/FilterList.vue'

describe('FilterList', () => {
  test('is a Vue instance', () => {
    const wrapper = shallowMount(FilterList)
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
