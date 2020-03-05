import { shallowMount } from '@vue/test-utils'

import Search from './Search.vue'

const wrapper = shallowMount(Search, {
  stubs: {
    svgIcon: '<span></span>'
  }
})

describe('Search', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
