<script lang="ts">
    import { type ExtensionContext } from '@beamable/portal-toolkit'
    import EdgegapOverview from './lib/EdgegapOverview.svelte'

    export let context: ExtensionContext
</script>

<EdgegapOverview {context} />