import { shallowMount } from '@vue/test-utils'

import User from '@/pages/User.vue'

const wrapper = shallowMount(User)

describe('User page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
