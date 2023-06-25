// eslint-disable-next-line @typescript-eslint/no-var-requires
const pkg = require("./package.json")

module.exports = {
  lintOnSave: true,

  transpileDependencies: ["vuetify"],
  configureWebpack: (config) => {
    config.externals = {
      "better-sqlite3": "commonjs better-sqlite3",
    }
  },

  chainWebpack: (config) => {
    config.plugin("html").tap((args) => {
      args[0].title = pkg.productName
      return args
    })
  },

  pluginOptions: {
    electronBuilder: {
      preload: "src/api/preload.ts",
      externals: ["better-sqlite3"],
      builderOptions: {
        nsis: {
          artifactName: pkg.productName + ".setup.${ext}",
          uninstallDisplayName: pkg.productName,
        },
      },
    },
  },
}
