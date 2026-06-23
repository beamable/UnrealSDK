import { StrictMode } from 'react'
import { createRoot, type Root } from 'react-dom/client'
import { Portal, type ExtensionContext } from '@beamable/portal-toolkit'
import './app.css'
import App from './App'

Portal.registerExtension({
  beamId: 'PushNotifications',
  onMount: (container, context: ExtensionContext) => {
    const root: Root = createRoot(container)
    root.render(
      <StrictMode>
        <App context={context} />
      </StrictMode>,
    )
    return root
  },
  onUnmount: (instance) => {
    (instance as Root).unmount()
  },
})
