import { useQuery, useResult } from '@vue/apollo-composable'

export default function useRoute ({ query, variables }) {
  const { result, loading, error } = useQuery(query, variables)

  const data = useResult(result, null, (data) => {
    if (data.route) { return data.route }
    return null
  })

  return {
    data,
    loading,
    error
  }
}
