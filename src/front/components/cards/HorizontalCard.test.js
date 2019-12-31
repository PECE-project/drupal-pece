import { shallowMount } from '@vue/test-utils'

import HorizontalCard from './HorizontalCard'

const wrapper = shallowMount(HorizontalCard)

describe('HorizontalCard', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
