import { defineConfig } from 'vite'
import react from '@vitejs/plugin-react'
import { portalExtensionPlugin } from '@beamable/portal-toolkit/vite'

// React, react-dom, react-dom/client, and react/jsx-runtime are all
// externalized by `portalExtensionPlugin({ react: true })` so the bundle
// does NOT include its own React copy. The Portal host assigns matching
// window globals before the extension's IIFE runs. Keep the externals in
// sync with what your code imports to avoid "Invalid hook call" at runtime.
export default defineConfig({
  plugins: [react(), portalExtensionPlugin({ react: true })],
  resolve: {
    dedupe: []
  },
  build: {
    minify: false,
    outDir: 'assets',
    lib: {
      entry: 'src/main.tsx',
      name: 'PushNotifications',
      formats: ['iife'],
    },
    rollupOptions: {
      input: 'src/main.tsx',
      output: {
        format: 'iife',
        inlineDynamicImports: true,
        entryFileNames: 'index.js',
        assetFileNames: (assetInfo) => {
          if (assetInfo.name && assetInfo.name.endsWith('.css')) {
            return 'style.css'
          }
          return '[name][extname]'
        },
      },
    },
  },
})
