/**
 * Commit Message Format:
 *
 * <type>(<scope>): <subject>
 * <body>
 * <footer>
 *
 * The first line is also called header
 */

/** @type {import('@commitlint/types').UserConfig} */
module.exports = {
  rules: {
    // header
    "header-max-length": [2, "always", 72],
    "header-min-length": [2, "always", 10],

    // type
    "type-enum": [
      2,
      "always",
      [
        "build",
        "chore",
        "ci",
        "docs",
        "feat",
        "fix",
        "refactor",
        "style",
        "test",
      ],
    ],
    "type-case": [2, "always", "lower-case"],
    "type-empty": [2, "never"],

    // scope
    "scope-enum": [2, "always", ["web", "i18n", "api"]],
    "scope-case": [2, "always", "lower-case"],
    "scope-empty": [0],

    // subject
    "subject-case": [
      2,
      "never",
      [
        "upper-case",
        "pascal-case",
        "sentence-case",
        "snake-case",
        "start-case",
      ],
    ],
    "subject-empty": [2, "never"],
    "subject-full-stop": [2, "never", "."],
    "subject-exclamation-mark": [2, "never"],

    // body
    "body-leading-blank": [2, "always"],
    // footer
    "footer-leading-blank": [2, "always"],
  },
}
