import VueTestUtils from '@vue/test-utils'

import translations from './lang/en-US'

VueTestUtils.config.mocks.$t = msg => translations[msg]
