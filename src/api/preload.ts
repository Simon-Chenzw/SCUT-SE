import { contextBridge } from "electron"

import * as api_website from "./api_website"
contextBridge.exposeInMainWorld("api_website", api_website)

import * as api_url from "./api_url"
contextBridge.exposeInMainWorld("api_url", api_url)

import * as api_fund from "./api_fund"
contextBridge.exposeInMainWorld("api_fund", api_fund)
