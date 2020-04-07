import ForgotPass from '@/pages/auth/ForgotPass'
import Register from '@/pages/auth/Register'
import ResetPass from '@/pages/auth/ResetPass'

export default [
  {
    path: '/register',
    name: 'register___en',
    component: Register
  },
  {
    path: '/forgot-password',
    name: 'forget-password___en',
    component: ForgotPass
  },
  {
    path: '/recover-password',
    name: 'recover-password___en',
    component: ResetPass
  }
]
