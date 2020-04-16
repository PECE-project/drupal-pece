import { useQuery, useResult } from '@vue/apollo-composable'
import { ref } from '@vue/composition-api'

export default async function useGqlMultipleContents ({ queries, globalVariables }) {
  const data = ref([])
  const errors = ref([])
  const loading = ref(false)

  const promises = Object.keys(queries).map(async (queryName) => {
    const { result, loading, error } = await useQuery(queries[queryName].query, (queries[queryName].variables || globalVariables))
    errors.value = [...errors.value, error]
    loading.value = loading

    await useResult(result, null, (data) => {
      data.value = [...data.value, {
        total: data[queryName].total,
        items: data[queryName].items
      }]
    })
  })

  await Promise.all(promises)

  return {
    data,
    errors,
    loading
  }
}
