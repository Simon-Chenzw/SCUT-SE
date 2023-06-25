/**
 * @type {import('next-i18next').UserConfig}
 */
const i18NextConfig = {
  i18n: {
    defaultLocale: "en",
    locales: ["en", "zh-Hans"],
  },
  reloadOnPrerender: process.env.NODE_ENV === "development",
}

module.exports = i18NextConfig
