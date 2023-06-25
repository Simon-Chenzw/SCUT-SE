import type { NextRequest } from "next/server"
import { NextResponse } from "next/server"

export const config = {
  matcher: [
    /*
     * Match all request paths except for the ones starting with:
     * - api (API routes)
     * - _next/static (static files)
     * - _next/image (image optimization files)
     * - favicon.ico (favicon file)
     */
    "/",
    "/((?!api|_next/static|_next/image|favicon.ico).*)",
  ],
}

export async function middleware(request: NextRequest) {
  if (request.nextUrl.pathname.startsWith("/auth")) return

  const resp = await fetch(new URL("/api/auth/me", request.nextUrl.origin), {
    headers: {
      cookie: request.headers.get("cookie") || "",
    },
  })
  if ((await resp.json()).code !== 0)
    return NextResponse.redirect(
      new URL(`/${request.nextUrl.locale}/auth`, request.url)
    )
}
