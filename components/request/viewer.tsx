import RequestImageViewerItem from "@/components/request/viewer-item"
import { MachinedResultObject, RequestObject } from "@/lib/api/request"
import { Modal } from "@mantine/core"
import { useMediaQuery } from "@mantine/hooks"
import { useEffect, useRef, useState } from "react"

class ResultObject {
  constructor(
    private canvas: HTMLCanvasElement,
    private canvasCtx: CanvasRenderingContext2D,
    public data: MachinedResultObject
  ) {
    this.deactive()
  }

  isInside(x: number, y: number): boolean {
    return (
      this.data.region.x <= x &&
      x <= this.data.region.x + this.data.region.w &&
      this.data.region.y <= y &&
      y <= this.data.region.y + this.data.region.h
    )
  }

  active() {
    this.canvasCtx.lineWidth =
      Math.min(this.canvas.width, this.canvas.height) / 200
    this.canvasCtx.setLineDash([20, 20])
    this.canvasCtx.strokeStyle = "red"
    this.canvasCtx.strokeRect(
      this.data.region.x,
      this.data.region.y,
      this.data.region.w,
      this.data.region.h
    )
  }

  deactive() {
    this.canvasCtx.lineWidth =
      Math.min(this.canvas.width, this.canvas.height) / 200
    this.canvasCtx.setLineDash([20, 20])
    this.canvasCtx.strokeStyle = "cyan"
    this.canvasCtx.strokeRect(
      this.data.region.x,
      this.data.region.y,
      this.data.region.w,
      this.data.region.h
    )
  }
}

class ResultObjectList {
  private list: ResultObject[]
  private _active?: ResultObject

  constructor(
    private canvas: HTMLCanvasElement,
    private canvasCtx: CanvasRenderingContext2D,
    regions: MachinedResultObject[],
    onClick?: (region: ResultObject) => void
  ) {
    this.list = regions.map((v) => new ResultObject(canvas, canvasCtx, v))

    canvas.addEventListener("mousemove", (ev: MouseEvent) => {
      const rect = this.canvas.getBoundingClientRect()
      const x = (ev.clientX - rect.left) * (this.canvas.width / rect.width)
      const y = (ev.clientY - rect.top) * (this.canvas.height / rect.height)
      this.active = this.list.find((v) => v.isInside(x, y))
    })

    canvas.addEventListener("click", (ev: MouseEvent) => {
      const rect = this.canvas.getBoundingClientRect()
      const x = (ev.clientX - rect.left) * (this.canvas.width / rect.width)
      const y = (ev.clientY - rect.top) * (this.canvas.height / rect.height)
      this.active = this.list.find((v) => v.isInside(x, y))
      if (onClick && this.active) onClick(this.active)
    })
  }

  set active(region: ResultObject | undefined) {
    if (this._active && this._active != region) this._active.deactive()
    if (region) region.active()
    this._active = region
  }

  get active(): ResultObject | undefined {
    return this._active
  }
}

////////////////////////////////////////////////////////////////////////////////
// hook

function useViewer(
  ref: React.RefObject<HTMLCanvasElement>,
  image: HTMLImageElement | undefined,
  machinedResult: NonNullable<RequestObject["machinedResult"]>
): [MachinedResultObject | undefined, () => void] {
  const [region, setRegion] = useState<MachinedResultObject>()
  const [resultObjectList, setResultObjectList] = useState<ResultObjectList>()

  useEffect(() => {
    if (image === undefined) return
    const canvas = ref.current
    if (canvas === null) return
    const ctx = canvas.getContext("2d")
    if (ctx === null) return

    canvas.width = image.width
    canvas.height = image.height
    ctx.drawImage(image, 0, 0)

    const data = machinedResult.data as unknown as MachinedResultObject[]
    setResultObjectList(
      new ResultObjectList(canvas, ctx, data, (region) =>
        setRegion(region.data)
      )
    )
  }, [ref, image, machinedResult])

  return [
    region,
    () => {
      if (resultObjectList) resultObjectList.active = undefined
      setRegion(undefined)
    },
  ]
}

////////////////////////////////////////////////////////////////////////////////

export default function RequestImageViewer(props: {
  image: HTMLImageElement | undefined
  machinedResult: NonNullable<RequestObject["machinedResult"]>
}) {
  const isMobile = useMediaQuery("(max-width: 50em)")
  const ref = useRef<HTMLCanvasElement>(null)
  const [object, resetObject] = useViewer(
    ref,
    props.image,
    props.machinedResult
  )

  return (
    <>
      <canvas
        ref={ref}
        style={{
          maxWidth: "100%",
          maxHeight: "100%",
        }}
      />
      <Modal
        opened={object !== undefined}
        onClose={() => resetObject()}
        title={object?.area}
        fullScreen={isMobile}
        transitionProps={{ transition: "fade", duration: 200 }}
      >
        <RequestImageViewerItem image={props.image} object={object} />
      </Modal>
    </>
  )
}
