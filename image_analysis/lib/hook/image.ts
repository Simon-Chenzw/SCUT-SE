import { RequestObject } from "@/lib/api/request"
import { useEffect, useState } from "react"

export function useImageElement(
  imageSrc: string | undefined
): HTMLImageElement | undefined {
  const [imageElement, setImageElement] = useState<HTMLImageElement>()

  useEffect(() => {
    if (imageSrc !== undefined) {
      const imageElement = new Image()
      imageElement.src = imageSrc
      imageElement.decode().then(() => setImageElement(imageElement))
    } else {
      setImageElement(undefined)
    }
  }, [imageSrc])

  return imageElement
}

export function useImage(
  image: RequestObject["image"]
): HTMLImageElement | undefined {
  const [imageSrc, setImageSrc] = useState<string>()
  const imageElement = useImageElement(imageSrc)

  useEffect(() => {
    if (image) setImageSrc(`/api/image/${image.id}`)
    else setImageSrc(undefined)
  }, [image])

  return imageElement
}
