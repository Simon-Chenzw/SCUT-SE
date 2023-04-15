import { useRouter } from "next/router"
import { useEffect, useState } from "react"

export function useTab(tabs: [string, string][]) {
  const router = useRouter()
  const defaultTab = tabs[0][0]
  const [tab, setTab] = useState(defaultTab)

  useEffect(() => {
    if (!router.isReady) return
    const t = Array.isArray(router.query.t)
      ? router.query.t.at(0)
      : router.query.t
    setTab(t || defaultTab)
  }, [router])

  const setQueryTab = (t: string) => {
    setTab(t)
    if (t === defaultTab) {
      // eslint-disable-next-line @typescript-eslint/no-unused-vars
      const { t, ...query } = router.query
      router.push({ query }, undefined, { shallow: true })
    } else {
      const query = { ...router.query, t }
      router.push({ query }, undefined, { shallow: true })
    }
  }

  return [tab, setQueryTab, tabs] as const
}
