import { shallowMount } from '@vue/test-utils'

import Logo from '@/components/Logo.vue'

describe('Logo', () => {
  test('is a Vue instance', () => {
    const wrapper = shallowMount(Logo)
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
