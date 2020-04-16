import { DefaultApolloClient } from '@vue/apollo-composable'
import { provide } from '@vue/composition-api'

export default ({ app }) => {
  app.setup = () => {
    const apolloClient = app.apolloProvider.defaultClient

    provide(DefaultApolloClient, apolloClient)
  }
}
