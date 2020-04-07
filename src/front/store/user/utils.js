import { GET_USER } from '@/graphql/queries/user'
import api from '@/services/api'
import * as MUTATIONS_TYPES from './mutation-types' // eslint-disable-line

export function makeAuth (commit, formData) {
  const apolloClient = this.apolloProvider.defaultClient
  return api('/oauth/token', {
    method: 'POST',
    body: formData
  })
    .then(async (res) => {
      if (res.error) { throw (res) }

      commit(MUTATIONS_TYPES.AUTH_SUCCESS, {
        token: res.access_token,
        refreshToken: res.refresh_token
      })

      const { data } = await apolloClient.query({
        query: GET_USER,
        variables: { id: res.user_id },
        context: {
          headers: {
            authorization: `Bearer ${res.access_token}`
          }
        }
      })

      commit(MUTATIONS_TYPES.SET_USER, data.user)
      commit(MUTATIONS_TYPES.AUTH_STATUS_REQUEST, 'success')
      return res
    })
    .catch((error) => {
      commit(MUTATIONS_TYPES.AUTH_STATUS_REQUEST, 'error')
      return error
    })
}
