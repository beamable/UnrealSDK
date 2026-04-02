import { defineConfig } from 'vite'
import { svelte } from '@sveltejs/vite-plugin-svelte'
import { portalExtensionPlugin } from '@beamable/portal-toolkit/vite'

export default defineConfig({
  plugins: [svelte(), portalExtensionPlugin()],
  resolve: {
    dedupe: []
  },
  build: {
    minify: false,
    outDir: 'assets',
    lib: {
      entry: 'src/main.js',
      name: 'edgegap_extensions',
      formats: ['iife'],
    },
    rollupOptions: {
      input: 'src/main.js',
      output: {
        format: 'iife',
        inlineDynamicImports: true,
        entryFileNames: 'main.js',
        assetFileNames: (assetInfo) => {
          if (assetInfo.name && assetInfo.name.endsWith('.css')) {
            return 'main.css'
          }
          return '[name][extname]'
        },
      },
    },
  },
})
