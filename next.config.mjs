import { PrismaPlugin } from "@prisma/nextjs-monorepo-workaround-plugin"

/**
 * @type {import('next').NextConfig}
 */
const nextConfig = {
  webpack: (config, { isServer }) => {
    if (isServer) {
      config.plugins = [...config.plugins, new PrismaPlugin()]
    }
    return config
  },
}

export default nextConfig
