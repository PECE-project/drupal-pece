import { shallowMount } from '@vue/test-utils'

import SimpleCard from './SimpleCard'

const wrapper = shallowMount(SimpleCard)

describe('SimpleCard', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
