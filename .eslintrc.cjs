/** @type {import('eslint').Linter.Config} */
module.exports = {
  env: {
    browser: true,
    es2021: true,
  },
  extends: [
    "eslint:recommended",
    "plugin:react/recommended",
    "plugin:react/jsx-runtime",
    "plugin:@typescript-eslint/recommended",
    "next/core-web-vitals",
    "prettier",
  ],
  overrides: [],
  parser: "@typescript-eslint/parser",
  parserOptions: {
    ecmaVersion: "latest",
    sourceType: "module",
  },
  plugins: ["react", "@typescript-eslint"],
  rules: {
    "react-hooks/exhaustive-deps": "off",
    "no-restricted-imports": [
      "error",
      {
        paths: [
          {
            name: "react-i18next",
            importNames: ["useTranslation"],
            message: "Import useTranslation from next-i18next instead.",
          },
        ],
      },
    ],
  },
  ignorePatterns: ["lib/prisma-client/*"],
}
