import { shallowMount } from '@vue/test-utils'

import Home from '@/pages/Home.vue'

const wrapper = shallowMount(Home)

describe('Home page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
