import { shallowMount } from '@vue/test-utils'

import Masonry from '@/components/Masonry.vue'

const wrapper = shallowMount(Masonry)

describe('Masonry', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
