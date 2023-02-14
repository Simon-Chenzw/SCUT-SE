module.exports = {
  "*.{js,ts,jsx,tsx}": ["yarn lint", "yarn format"],
  "!*.{js,ts,jsx,tsx}": ["yarn format"],
}
