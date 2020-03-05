export function useSlug (value) {
  const mapLetters = {
    a: /(á|ã|â|à)/g,
    e: /(é|ê)/g,
    i: /(í)/g,
    o: /(ó|ô|õ)/g,
    u: /(ú)/g,
    c: /(ç)/g,
    n: /(ñ)/g
  }
  for (const letter in mapLetters) {
    const rexp = mapLetters[letter]
    value = value.toLowerCase() // :) Avoid include capital letters in regex
      .replace(rexp, letter)
      .replace(/(\s|\.)/g, '-') // Replace space by delimiter '-'
  }

  return value
}
