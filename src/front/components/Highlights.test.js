import { shallowMount } from '@vue/test-utils'

import Highlights from './Highlights'
import { highlights } from '@/utils/fake'

const wrapper = shallowMount(Highlights)

describe('Highlights', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })

  test('Should render all items', () => {
    expect(wrapper.findAll('[data-pece="highlights-items"]').length).toBe(highlights.length)
  })

  test('First item must be enabled', () => {
    const first = wrapper.findAll('[data-pece="highlights-items"]').at(0)
    expect(first.classes()).toContain('highlights__list__item--active')
  })

  test('the first item should be highlighted', () => {
    const featured = wrapper.find('[data-pece="highlights-cover"]')
    expect(featured.attributes('href')).toBe(highlights[0].link)
  })

  test('Should choose an item to highlight', async () => {
    const index = 1
    wrapper.findAll('[data-pece="highlights-items"]').at(index).trigger('click')
    await wrapper.vm.$nextTick()
    expect(wrapper.find('[data-pece="highlights-cover"]').attributes('href')).toBe(highlights[index].link)
  })
})
