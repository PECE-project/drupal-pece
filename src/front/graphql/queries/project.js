import gql from 'graphql-tag'

export const GET_PROJECTS_ABOUT = gql`
  query ($offset: Int!, $limit: Int!) {
    peceProjects (offset: $offset, limit: $limit, filters: [
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
