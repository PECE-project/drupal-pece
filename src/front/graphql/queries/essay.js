import gql from 'graphql-tag'

export const GET_ESSAYS_HOME = gql`
  query ($offset: Int!, $limit: Int!) {
    peceEssays (offset: $offset, limit: $limit, filters: [
      { key: "status", value: "1" },
    ]) {
      total
      items {
        id
        title
        created
        thumbnail {
          alt
          url(style: THUMBNAIL_100x100)
        }
        tags {
          id
          title
        }
        author {
          id
          username
        }
      }
    }
  }
`
