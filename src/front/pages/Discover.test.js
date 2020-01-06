import { shallowMount } from '@vue/test-utils'

import Discover from '@/pages/Discover.vue'

const wrapper = shallowMount(Discover)

describe('Discover page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
