import About from '~/pages/About'
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
    component: About // Using component about avoid warning console
  },
  {
    path: '/analyze',
    name: 'analyze___en',
    component: About
  },
  {
    path: '/discover',
    name: 'discover___en',
    component: About
  }
]
