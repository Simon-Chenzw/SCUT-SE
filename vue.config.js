module.exports = {
  lintOnSave: true,

  transpileDependencies: ["vuetify"],
  configureWebpack: (config) => {
    config.externals = {
      "better-sqlite3": "commonjs better-sqlite3",
    }
  },
  pluginOptions: {
    electronBuilder: {
      preload: "src/api/preload.ts",
      externals: ["better-sqlite3"],
    },
  },
}
