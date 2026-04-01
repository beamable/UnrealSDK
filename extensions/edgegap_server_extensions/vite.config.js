import { defineConfig } from 'vite'
import { svelte } from '@sveltejs/vite-plugin-svelte'

export default defineConfig({
  plugins: [svelte()],
  resolve: {
    dedupe: []
  },
  build: {
    minify: false,
    outDir: 'assets',
    lib: {
      entry: 'src/main.js',
      name: 'edgegap_server_extensions',
      formats: ['iife'],
    },
    rollupOptions: {
      external: ['beamable-sdk', 'beamable-api'],
      input: 'src/main.js',
      output: {
        format: 'iife',
        inlineDynamicImports: true,
        globals: {
          'beamable-sdk': 'Beamable',
          'beamable-api': 'BeamableAPI'
        },
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
