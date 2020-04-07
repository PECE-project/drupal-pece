import gql from 'graphql-tag'

export const GET_USER = gql`
  query ($id: Int) {
    user (id: $id) {
      username
    }
  }
`

export const CREATE_USER = gql`
  mutation (
    $mail: String!,
    $username: String!,
    $pass: String!,
    $zotero: String,
    $status: Boolean
  ) {
    createPeople (
      data: {
        mail: $mail,
        username: $username,
        pass: $pass,
        zotero: $zotero,
        status: $status,
      }
    ) {
      id
    }
  }
`
