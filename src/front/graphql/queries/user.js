import gql from 'graphql-tag'

export const GET_USER = gql`
  query ($id: Int) {
    user (id: $id) {
      username
    }
  }
`
