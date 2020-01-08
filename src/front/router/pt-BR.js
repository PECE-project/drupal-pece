import About from '@/pages/About'
import Analyze from '@/pages/Analyze'
import AnalyzeQuestions from '@/pages/AnalyzeQuestions'
import Collaborate from '@/pages/Collaborate'
import Discover from '@/pages/Discover'
import Group from '@/pages/Group'
import Home from '@/pages/Home'
import User from '@/pages/User'

export default [
  {
    path: '/pt',
    name: 'home___pt',
    component: Home
  },
  {
    path: '/pt/sobre',
    name: 'about___pt',
    component: About
  },
  {
    path: '/pt/repo/grupos',
    name: 'collaborate___pt',
    component: Collaborate
  },
  {
    path: '/pt/repo/analise',
    name: 'analyze___pt',
    component: Analyze
  },
  {
    path: '/pt/repo/explorar',
    name: 'discover___pt',
    component: Discover
  },
  {
    path: '/pt/perguntas-de-analise-estruturada/:slug',
    name: 'questions_structured_analyze___pt',
    component: AnalyzeQuestions
  },
  {
    path: '/pt/grupo/:slug',
    name: 'group___pt',
    component: Group
  },
  {
    path: '/pt/user/:slug',
    name: 'user___pt',
    component: User
  }
]
