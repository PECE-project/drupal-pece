import About from '@/pages/About'
import Analyze from '@/pages/Analyze'
import AnalyzeQuestions from '@/pages/AnalyzeQuestions'
import Collaborate from '@/pages/Collaborate'
import Discover from '@/pages/Discover'
import Group from '@/pages/Group'
import Home from '@/pages/Home'
import Tag from '@/pages/Tag'
import User from '@/pages/User'

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
    component: Discover
  },
  {
    path: '/structured-analytics-questions-set/:slug',
    name: 'questions_structured_analyze___en',
    component: AnalyzeQuestions
  },
  {
    path: '/group/:slug',
    name: 'group___en',
    component: Group
  },
  {
    path: '/user/:slug',
    name: 'user___en',
    component: User
  },
  {
    path: '/tag/:slug',
    name: 'tag___en',
    component: Tag
  }
]
