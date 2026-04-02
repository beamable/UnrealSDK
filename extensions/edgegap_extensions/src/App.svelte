<script lang="ts">

    import {Beam, type ExtensionContext} from '@beamable/portal-toolkit'
    import EdgegapServers from './lib/EdgegapServers.svelte';

    export let context: ExtensionContext

    let beam: Beam

    context.beam.then(b => beam = b);

</script>

<EdgegapServers {context}/>
