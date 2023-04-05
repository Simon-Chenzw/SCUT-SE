import { ResponseBase } from "@/lib/api"

export interface ImageUploadResponse extends ResponseBase {
  data?: {
    iid: string
  }
}

export async function imageUploadToRequest(
  rid: string,
  payload: File
): Promise<ImageUploadResponse> {
  const form = new FormData()
  form.set("image", payload)

  const resp = await fetch(`/api/image/upload/${rid}`, {
    method: "POST",
    body: form,
  })

  return await resp.json()
}
