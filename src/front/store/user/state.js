export default function state () {
  return {
    user: {},
    auth: {
      token: '',
      refreshToken: ''
    },
    status: 'success'
  }
}
