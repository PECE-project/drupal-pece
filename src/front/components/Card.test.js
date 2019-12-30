import { shallowMount } from '@vue/test-utils'

import Card from './Card'

const wrapper = shallowMount(Card)

describe('Card', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
