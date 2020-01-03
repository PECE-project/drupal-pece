import About from '~/pages/About'
import Analyze from '~/pages/Analyze'
import AnalyzeQuestions from '~/pages/AnalyzeQuestions'
import Collaborate from '~/pages/Collaborate'
import Home from '~/pages/Home'

export default [
  {
    path: '/',
    name: 'home___en',
    component: Home
  },
  {
    path: '/about',
    name: 'about___en',
    component: About
  },
  {
    path: '/repo/collaborate',
    name: 'collaborate___en',
    component: Collaborate
  },
  {
    path: '/repo/analyze',
    name: 'analyze___en',
    component: Analyze
  },
  {
    path: '/repo/discover',
    name: 'discover___en',
    component: About // Using Page About avoid warning console
  },
  {
    path: '/structured-analytics-questions-set/:slug',
    name: 'questions_structured_analyze___en',
    component: AnalyzeQuestions
  }
]
