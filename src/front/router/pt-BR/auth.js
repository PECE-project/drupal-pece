import ForgotPass from '@/pages/auth/ForgotPass'
import Register from '@/pages/auth/Register'
import ResetPass from '@/pages/auth/ResetPass'

export default [
  {
    path: '/cadastrar',
    name: 'register___pt',
    component: Register
  },
  {
    path: '/esqueci-senha',
    name: 'forget-password___pt',
    component: ForgotPass
  },
  {
    path: '/recuperar-senha',
    name: 'recover-password___pt',
    component: ResetPass
  }
]
