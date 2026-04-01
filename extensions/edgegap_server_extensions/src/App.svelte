<script>
  import EdgegapServers from './lib/EdgegapServers.svelte'
  import { Context } from './store'

  export let context

  $: Context.set(context)
</script>

<EdgegapServers /> 