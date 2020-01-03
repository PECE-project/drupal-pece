import { shallowMount } from '@vue/test-utils'

import Analyze from '@/pages/Analyze.vue'

const wrapper = shallowMount(Analyze)

describe('Analyze page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
