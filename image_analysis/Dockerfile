FROM node:18.15.0-alpine as builder

WORKDIR /app

ENV NODE_ENV production
ENV NEXT_TELEMETRY_DISABLED 1

# Install dependencies
COPY .yarn .yarn
COPY yarn.lock .yarnrc.yml .
COPY package.json .
RUN --mount=type=cache,target=/root/.cache \
    --mount=type=cache,target=/root/.yarn/berry/cache \
    yarn install --immutable

# Build lib/prisma-client
COPY schema.prisma .
RUN yarn pnpify prisma generate

# Build website
COPY . .
RUN yarn build

# Remove unnecessary dependencies which will conflict
RUN rm -rf /app/.next/standalone/.yarn/cache

###############################################################################

FROM node:18.15.0-alpine as runner

WORKDIR /app
EXPOSE 3000

ENV PORT 3000
ENV NODE_ENV production

# Install dependencies
COPY .yarn .yarn
COPY yarn.lock .yarnrc.yml .
COPY package.json .
RUN --mount=type=cache,target=/root/.cache \
    --mount=type=cache,target=/root/.yarn/berry/cache \
    yarn workspaces focus --all --production && \
    # Remove unnecessary dependencies make the image smaller
    find .yarn/cache -name '@next-swc-*.zip' -delete && \
    find .yarn/cache -name 'typescript-*.zip' -delete && \
    find .yarn/unplugged -path '.yarn/unplugged/@next-swc-*' -delete

# Copy needed files for runtime
COPY next-i18next.config.js .
COPY ./public ./public
COPY --from=builder /app/.next/standalone .
COPY --from=builder /app/.next/static .next/static

USER node

CMD ["node", "-r", "./.pnp.cjs", "server.js"]
