import { RequestObject } from "@/lib/api/request"
import { useEffect, useRef } from "react"

async function initCanvas(
  canvas: HTMLCanvasElement,
  image: NonNullable<RequestObject["image"]>
): Promise<void> {
  const imageElement = new Image()
  imageElement.src = `/api/image/${image.id}`
  await imageElement.decode()

  canvas.width = imageElement.width
  canvas.height = imageElement.height
  canvas.getContext("2d")?.drawImage(imageElement, 0, 0)
}

export default function RequestImageViewer(props: {
  image: NonNullable<RequestObject["image"]>
  machinedResult: NonNullable<RequestObject["machinedResult"]>
}) {
  const ref = useRef<HTMLCanvasElement>(null)

  useEffect(() => {
    if (ref.current) initCanvas(ref.current, props.image)
  }, [ref, props.image, props.machinedResult])

  return (
    <canvas
      ref={ref}
      style={{
        maxWidth: "100%",
        maxHeight: "100%",
      }}
    />
  )
}
