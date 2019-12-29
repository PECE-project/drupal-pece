import { shallowMount } from '@vue/test-utils'

import Navigation from './Navigation'
import { menuHeader } from '@/utils/fake'

const wrapper = shallowMount(Navigation)

describe('Navigation', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })

  test('Should render all items', () => {
    expect(wrapper.findAll('[data-pece="menuHeader-items"]').length).toBe(menuHeader.length)
  })
})
