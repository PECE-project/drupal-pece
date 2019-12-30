import { shallowMount } from '@vue/test-utils'

import ListCards from './ListCards'

const wrapper = shallowMount(ListCards)

describe('ListCards', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
