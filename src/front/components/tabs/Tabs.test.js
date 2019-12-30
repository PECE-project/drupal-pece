import { shallowMount } from '@vue/test-utils'

import Tabs from './Tabs.vue'

describe('Tabs', () => {
  test('is a Vue instance', () => {
    const wrapper = shallowMount(Tabs)
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
