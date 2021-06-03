import { contextBridge } from "electron"

import * as api_website from "./api_website"
contextBridge.exposeInMainWorld("api_website", api_website)
