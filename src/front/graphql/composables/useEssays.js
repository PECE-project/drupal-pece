import { useQuery, useResult } from '@vue/apollo-composable'

export default function useEssays ({ query, variables }) {
  const { result, loading, error } = useQuery(query, variables)

  const essays = useResult(result, null, (data) => {
    if (data.peceEssays && data.peceEssays.items.length) { return data.peceEssays.items }
    return null
  })

  return {
    essays,
    loading,
    error
  }
}
