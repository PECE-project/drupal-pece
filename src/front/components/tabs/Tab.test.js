import { shallowMount } from '@vue/test-utils'

import Tab from './Tab.vue'

describe('Tab', () => {
  test('is a Vue instance', () => {
    const wrapper = shallowMount(Tab)
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
