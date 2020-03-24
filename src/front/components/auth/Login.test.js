import { shallowMount } from '@vue/test-utils'

import Login from '@/components/auth/Login.vue'

const wrapper = shallowMount(Login)

describe('Login', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
