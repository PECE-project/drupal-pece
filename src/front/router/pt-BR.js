import About from '~/pages/About'
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
    component: About // Using component about avoid warning console
  },
  {
    path: '/pt/analyze',
    name: 'analyze___pt',
    component: About
  },
  {
    path: '/pt/discover',
    name: 'discover___pt',
    component: About
  }
]
