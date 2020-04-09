import gql from 'graphql-tag'

export const GET_ROUTE = gql`
  query ($path: String!) {
    route (path: $path) {
      id
      title
      body
    }
  }
`
