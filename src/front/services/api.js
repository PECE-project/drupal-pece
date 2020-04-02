export default function api (path, options) {
  return new Promise((resolve, reject) => {
    fetch(`${process.env.NUXT_API_HTTP}${path}`, options)
      .then(response => response.json())
      .then(data => resolve(data))
      .catch(error => reject(error))
  })
}
