<script lang="ts">

    import {Beam, type ExtensionContext} from '@beamable/portal-toolkit'
    import EdgegapServers from './lib/EdgegapServers.svelte';
    import BeamableInit from './lib/BeamableInit.svelte';
    export let context: ExtensionContext

    let beam: Beam

    context.beam.then(b => beam = b);

</script>

<EdgegapServers/>
<BeamableInit/>
<beam-card style="margin-bottom: 20px">
    <beam-card-title>
        edgegap_extensions
    </beam-card-title>
    <beam-card-text>
        <div  style="padding: 18px">
            <div>
                Player ID {beam?.player.id}
            </div>
            <beam-btn color="primary">
                Click
            </beam-btn>
        </div>
    </beam-card-text>
</beam-card>