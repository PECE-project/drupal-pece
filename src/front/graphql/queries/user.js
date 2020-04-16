import gql from 'graphql-tag'

export const GET_USER = gql`
  query ($id: Int) {
    user (id: $id) {
      username
    }
  }
`

export const GET_USERS = gql`
  query ($offset: Int!, $limit: Int!) {
    users (offset: $offset, limit: $limit, filters: [
      { key: "status", value: "1" },
    ]) {
      total
      items {
        id
        mail
        username
        status
      }
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
