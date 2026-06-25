import { registerReactExtension } from '@beamable/portal-toolkit/react'
import { name as beamId } from '../package.json'
import './app.css'
import App from './App'

// `registerReactExtension` sets up createRoot, wraps the App in <StrictMode>,
// and registers mount/unmount with the host. `beamId` must equal package.json#name.
registerReactExtension({ beamId, App })
