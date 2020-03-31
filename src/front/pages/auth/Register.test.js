import Register from '@/pages/auth/Register'
import { shallowMount } from '@vue/test-utils'


const wrapper = shallowMount(Register)

describe('Register page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
