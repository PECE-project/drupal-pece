import { shallowMount } from '@vue/test-utils'

import CardTag from './CardTag'

const wrapper = shallowMount(CardTag)

describe('CardTag', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
