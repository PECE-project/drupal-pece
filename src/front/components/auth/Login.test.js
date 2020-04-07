import Login from '@/components/auth/Login.vue'
import { shallowMount } from '@vue/test-utils'

const wrapper = shallowMount(Login)

describe('Login', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
