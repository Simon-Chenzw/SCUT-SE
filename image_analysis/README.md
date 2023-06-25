# image_analysis

image analysis frontend, base on next.js

## Usage

- setup: `yarn install && yarn setup`
- dev: `yarn dev`
- build: `yarn build`
- build docker: `docker build -t image_analysis .`

## Requirements

- [vscode](https://code.visualstudio.com/#alt-downloads)
  - install `@recommended` [extensions](./.vscode/extensions.json)
    - Press `F1` and type `Extensions: Show Recommended Extensions`
- nodejs version manage
  - \[primary\] [nvm](https://github.com/nvm-sh/nvm#install--update-script)
  - \[Secondary\] [nvs](https://github.com/jasongin/nvs#setup) for windows
- [yarn](https://yarnpkg.com/getting-started/install)
  - `corepack enable`
- \[Build only\] install docker engine [guide](https://docs.docker.com/engine/install/#server)
  - docker desktop not required, just install docker engine

## Environment Setup

follow the steps below to setup the environment into `.env` file

### Staging PostgreSQL

```bash
docker run --name postgres-staging -e POSTGRES_PASSWORD=password -p 5432:5432 -d postgres:15.2
echo DATABASE_URL=postgresql://postgres:password@localhost:5432/postgres >> .env
yarn pnpify prisma db push
```

### JWT key

```Javascript
const crypto = require("crypto")
const fs = require("fs")

const key = crypto.generateKeyPairSync("rsa", {
  modulusLength: 4096,
  publicKeyEncoding: {
    type: "spki",
    format: "pem",
  },
  privateKeyEncoding: {
    type: "pkcs8",
    format: "pem",
  },
})

fs.appendFileSync(
  ".env",
  `\nPUBLIC_KEY="${key.publicKey.replaceAll(
    "\n",
    "\\n"
  )}"\n\nPRIVATE_KEY="${key.privateKey.replaceAll("\n", "\\n")}"\n`
)
```

### Wechat

setup these env

```sh
WECHAT_APP_ID=...
WECHAT_APP_SECRET=...
```
