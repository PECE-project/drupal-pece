export default function api ({ path, options, handlerError }) {
  return new Promise((resolve, reject) => {
    fetch(`${process.env.NUXT_API_HTTP}${path}`, options)
      .then(async (response) => {
        if (!response.ok) {
          if (handlerError) { handlerError(response) }
          const res = await response.json()
          throw new Error(res.message || 'Request error')
        }
        return response
      })
      .then(response => resolve(response.json()))
      .catch(error => reject(error))
  })
}
