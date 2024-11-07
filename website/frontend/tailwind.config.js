/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ], theme: {
    extend: {
      colors: {
        bluePrime: "#DBF5FD"
      },
      fontSize: {
        'xxs': '0.5rem'
      }
    },
  },
  plugins: [],
}

