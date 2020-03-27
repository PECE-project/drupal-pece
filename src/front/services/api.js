export default function api (path, options) {
  return new Promise((resolve, reject) => {
    fetch(`${process.env.VUE_APP_URL_API}${path}`, options)
      .then(response => response.json())
      .then(data => resolve(data))
      .catch(error => reject(error))
  })
}
