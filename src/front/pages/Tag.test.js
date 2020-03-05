import { shallowMount } from '@vue/test-utils'

import tag from '@/pages/tag.vue'

const wrapper = shallowMount(tag)

describe('tag page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
