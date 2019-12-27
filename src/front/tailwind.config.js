/*
** TailwindCSS Configuration File
**
** Docs: https://tailwindcss.com/docs/configuration
** Default: https://github.com/tailwindcss/tailwindcss/blob/master/stubs/defaultConfig.stub.js
*/
module.exports = {
  theme: {
    extend: {
      colors: {
        primary: '',
        accent: '#6C6FD4',
        accentHover: '#595BB5'
      },
      boxShadow: {
        pece: '0 6px 4px #F7FAFC'
      }
    }
  },
  variants: {
    borderWidth: ['responsive', 'hover', 'focus'],
    width: ['responsive', 'hover', 'focus']
  },
  plugins: []
}
