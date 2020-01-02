import { shallowMount } from '@vue/test-utils'

import About from '@/pages/About.vue'

const wrapper = shallowMount(About)

describe('About page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
