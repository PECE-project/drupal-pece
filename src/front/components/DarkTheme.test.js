import { shallowMount } from '@vue/test-utils'

import DarkTheme from '@/components/DarkTheme.vue'

const wrapper = shallowMount(DarkTheme, {
  stubs: {
    svgIcon: '<span></span>'
  }
})

describe('DarkTheme', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })

  test('Should contain a button.', () => {
    expect(wrapper.contains('button')).toBeTruthy()
  })

  test('Should contain a style tag with media none.', () => {
    expect(wrapper.find('style').attributes('media')).toBe('none')
  })

  test('Should contain a style tag with media screen when click button.', async () => {
    wrapper.find('button').trigger('click')
    await wrapper.vm.$nextTick()
    expect(wrapper.find('style').attributes('media')).toBe('screen')
  })
})
