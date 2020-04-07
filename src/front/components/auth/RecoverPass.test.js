import RecoverPassForm from '@/components/auth/RecoverPassForm.vue'
import { shallowMount } from '@vue/test-utils'

const wrapper = shallowMount(RecoverPassForm)

describe('RecoverPassForm', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
