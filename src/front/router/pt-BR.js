import About from '~/pages/About'
import Analyze from '~/pages/Analyze'
import AnalyzeQuestions from '~/pages/AnalyzeQuestions'
import Collaborate from '~/pages/Collaborate'
import Home from '~/pages/Home'

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
    component: About // Using component About avoid warning console
  },
  {
    path: '/pt/perguntas-de-analise-estruturada/:slug',
    name: 'questions_structured_analyze___pt',
    component: AnalyzeQuestions
  }
]
