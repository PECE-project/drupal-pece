import { shallowMount } from '@vue/test-utils'

import Navigation from './Navigation.vue'

describe('Navigation', () => {
  test('is a Vue instance', () => {
    const wrapper = shallowMount(Navigation)
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
