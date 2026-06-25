import { definePortalExtensionConfig } from '@beamable/portal-toolkit/vite'
import { name } from './package.json'

// The helper handles React externalization, IIFE library mode, and the
// `index.js` + `style.css` output naming the CLI expects. React, react-dom,
// react-dom/client, and react/jsx-runtime are externalized so the bundle does
// NOT ship its own React copy — the Portal host assigns matching window globals
// before the extension's IIFE runs.
export default definePortalExtensionConfig({ entry: 'src/main.tsx', name })
