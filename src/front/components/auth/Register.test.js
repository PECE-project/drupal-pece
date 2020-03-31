import Register from '@/components/auth/Register.vue'
import { shallowMount } from '@vue/test-utils'

const wrapper = shallowMount(Register)

describe('Register', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
