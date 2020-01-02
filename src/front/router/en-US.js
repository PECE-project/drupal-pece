import About from '~/pages/About'
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
    path: '/collaborate',
    name: 'collaborate___en',
    component: Collaborate
  },
  {
    path: '/analyze',
    name: 'analyze___en',
    component: About // Using Page About avoid warning console
  },
  {
    path: '/discover',
    name: 'discover___en',
    component: About // Using Page About avoid warning console
  }
]
