import { shallowMount } from '@vue/test-utils'

import Button from './Button.vue'

describe('BaseButton', () => {
  test('is a Vue instance', () => {
    const wrapper = shallowMount(Button)
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
