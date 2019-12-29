import Vue from 'vue'

import VueCompositionApi from '@vue/composition-api'
import VueTestUtils from '@vue/test-utils'

import translations from './lang/en-US'

Vue.use(VueCompositionApi)
VueTestUtils.config.mocks.$t = msg => translations[msg]
