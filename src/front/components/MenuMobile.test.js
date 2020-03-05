import { shallowMount } from '@vue/test-utils'

import MenuMobile from '@/components/MenuMobile.vue'
import Navigation from '@/components/Navigation.vue'

const wrapper = shallowMount(MenuMobile, {
  slots: {
    default: Navigation
  }
})

describe('MenuMobile', () => {
  test('is a Vue instance.', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })

  test('The menu should contain a button.', () => {
    expect(wrapper.contains('button')).toBeTruthy()
  })

  test('Should display menu when clicking', async () => {
    wrapper.find('button').trigger('click')
    await wrapper.vm.$nextTick()
    expect(wrapper.find('.main-menu').is('nav')).toBeTruthy()
  })

  /**
   * TODO: Ver uma maneira de testar componentes com transitions e slots que recebem props
  */
})
