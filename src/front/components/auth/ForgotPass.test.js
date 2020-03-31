import ForgotPassForm from '@/components/auth/ForgotPassForm.vue'
import { shallowMount } from '@vue/test-utils'

const wrapper = shallowMount(ForgotPassForm)

describe('ForgotPassForm', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
