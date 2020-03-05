import { shallowMount } from '@vue/test-utils'

import ListFilter from '@/components/ListFilter.vue'

describe('ListFilter', () => {
  test('is a Vue instance', () => {
    const wrapper = shallowMount(ListFilter)
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
