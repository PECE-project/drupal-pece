import { shallowMount } from '@vue/test-utils'

import Tab from './Tab'
import Tabs from './Tabs'

const tabWrapper = {
  render (h) {
    return h(Tab, { props: { label: 'Teste' } })
  }
}

const wrapper = shallowMount(Tabs, {
  slots: {
    default: tabWrapper
  }
})

describe('Tabs', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
