import ForgotPass from '@/pages/auth/ForgotPass'
import { shallowMount } from '@vue/test-utils'

const wrapper = shallowMount(ForgotPass)

describe('ForgotPass page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
