import { shallowMount } from '@vue/test-utils'

import Checkbox from './Checkbox.vue'

describe('BaseCheckbox', () => {
  test('is a Vue instance', () => {
    const wrapper = shallowMount(Checkbox)
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
