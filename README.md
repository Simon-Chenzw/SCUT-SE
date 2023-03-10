# image_analysis

image analysis frontend, base on next.js

## Usage

dev: `yarn install && yarn dev`

## Staging PostgreSQL

```bash
docker run --name postgres-staging -e POSTGRES_PASSWORD=password -p 5432:5432 -d postgres:15.2
echo DATABASE_URL=postgresql://postgres:password@localhost:5432/postgres >> .env
yarn pnpify prisma db push
```
