import { PrismaPlugin } from "@prisma/nextjs-monorepo-workaround-plugin"

/**
 * @type {import('next').NextConfig}
 */
const nextConfig = {
  reactStrictMode: true,
  output: "standalone",
  // sync with next-i18next.config.js
  i18n: {
    defaultLocale: "en",
    locales: ["en", "zh-Hans"],
  },
  webpack: (config, { isServer }) => {
    if (isServer) {
      config.plugins = [...config.plugins, new PrismaPlugin()]
    }
    return config
  },
}

export default nextConfig
