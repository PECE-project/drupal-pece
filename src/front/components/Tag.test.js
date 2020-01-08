import { shallowMount } from '@vue/test-utils'

import Tag from './Tag.vue'

const wrapper = shallowMount(Tag)

describe('Tag', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
