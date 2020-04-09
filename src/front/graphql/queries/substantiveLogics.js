import gql from 'graphql-tag'

export const GET_SUBSTANTIVE_LOGICS_ABOUT = gql`
  query ($offset: Int!, $limit: Int!) {
    peceSubstantiveLogics (offset: $offset, limit: $limit, filters: [
      { key: "status", value: "1" },
    ]) {
      total
      items {
        id
        title
        image {
          url (style: THUMBNAIL_100x100)
        }
      }
    }
  }
`
