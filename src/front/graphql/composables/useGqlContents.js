import { useQuery, useResult } from '@vue/apollo-composable'
import { ref } from '@vue/composition-api'

export default function useGqlContents ({ query, variables, type }) {
  const { result, loading, error } = useQuery(query, variables)
  const total = ref(null)

  const data = useResult(result, null, (data) => {
    if (data[type]) {
      if (data[type].items) {
        total.value = data[type].total
        return data[type].items
      }
      return data[type]
    }
    return null
  })

  return {
    data,
    error,
    total,
    loading
  }
}
