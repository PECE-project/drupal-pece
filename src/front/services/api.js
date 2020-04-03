export default function api (path, options) {
  return new Promise((resolve, reject) => {
    fetch(`${process.env.NUXT_API_HTTP}${path}`, options)
      .then(async (response) => {
        if (!response.ok) {
          const res = await response.json()
          throw new Error(res.message || 'Request error')
        }
        return response
      })
      .then(response => response.json())
      .then(data => resolve(data))
      .catch(error => reject(error))
  })
}
