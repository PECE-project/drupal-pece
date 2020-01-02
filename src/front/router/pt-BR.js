import About from '~/pages/About'
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
    path: '/pt/collaborate',
    name: 'collaborate___pt',
    component: Collaborate
  },
  {
    path: '/pt/analyze',
    name: 'analyze___pt',
    component: About // Using component About avoid warning console
  },
  {
    path: '/pt/discover',
    name: 'discover___pt',
    component: About // Using component About avoid warning console
  }
]
