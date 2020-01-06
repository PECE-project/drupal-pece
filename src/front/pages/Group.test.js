import { shallowMount } from '@vue/test-utils'

import Group from '@/pages/Group.vue'

const wrapper = shallowMount(Group)

describe('Group page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
