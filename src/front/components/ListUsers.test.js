import { shallowMount } from '@vue/test-utils'

import ListUsers from '@/components/ListUsers.vue'

describe('ListUsers', () => {
  test('is a Vue instance', () => {
    const wrapper = shallowMount(ListUsers)
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
