import { shallowMount } from '@vue/test-utils'

import Home from '@/pages/Home.vue'

describe('Home', () => {
  test('is a Vue instance', () => {
    const wrapper = shallowMount(Home, {
      mocks: {
        $t: key => key
      }
    })
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
