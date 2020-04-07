import ResetPass from '@/pages/auth/ResetPass'
import { shallowMount } from '@vue/test-utils'

const wrapper = shallowMount(ResetPass)

describe('ResetPass page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
