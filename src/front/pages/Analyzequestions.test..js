import { shallowMount } from '@vue/test-utils'

import AnalyzeQuestions from '@/pages/AnalyzeQuestions.vue'

const wrapper = shallowMount(AnalyzeQuestions)

describe('AnalyzeQuestions page', () => {
  test('is a Vue instance', () => {
    expect(wrapper.isVueInstance()).toBeTruthy()
  })
})
