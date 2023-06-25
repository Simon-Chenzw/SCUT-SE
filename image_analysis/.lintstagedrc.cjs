module.exports = {
  "*.{js,ts,jsx,tsx}": ["yarn lint --fix", "yarn format --write"],
  "!*.{js,ts,jsx,tsx}": ["yarn format --write"],
}
