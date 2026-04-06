<script>
  import { Beam } from '../store.js'

	let loading = false
  let error = null
	export let playerData = null

	async function init(){
		loading = true
    error = null

    try{
      playerData = {
        cid: $Beam.cid,
        pid: $Beam.pid,
        playerId: $Beam.player.id
      }

    } catch (err) {
      console.error('Failed to init player:', err)
      error = err.message
    } finally {
      loading = false
    }
	}

</script>

<beam-card>
  <beam-card-actions >
    <beam-btn          
      on:click={init}
      disabled={loading || playerData ? true : null}
      loading={loading ? true : null}
    >
      {#if loading}
        Initializing...
      {:else if playerData}
        Player Loaded
      {:else}
        Initialize Player
      {/if}
    </beam-btn>

    {#if error}
      <p class="error">{error}</p>
    {/if}
  </beam-card-actions>

  {#if playerData}
    <beam-data-table                                                                                                                                                                                                                                                                                                                             
      headers={[                                                                                                                                                                                                                                                                                                                              
        { text: 'Key',   value: 'key',   sortable: false },                                                                                                                                                                                                                                                                                   
        { text: 'Value', value: 'value', sortable: false },                                                                                                                                                                                                                                                                                   
      ]}                                                                                                                                                                                                                                                                                                                                      
      items={[                                                                                                                                                                                                                                                                                                                                
        { key: 'CID',       value: playerData.cid },                                                                                                                                                                                                                                                                                          
        { key: 'PID',       value: playerData.pid },                                                                                                                                                                                                                                                                                          
        { key: 'Player ID', value: playerData.playerId },                                                                                                                                                                                                                                                                                     
      ]}                                                                                                                                                                                                                                                                                                                                      
      dense                                                                                                                                                                                                                                                                                                                                   
      hide-default-footer
    ></beam-data-table>  
  {:else}
    <p class="placeholder">Click the button to load player data.</p>
  {/if}
</beam-card>

<style>
  .error {
    color: red;
    margin-top: 0.5rem;
    font-size: 0.9rem;
  }

  .placeholder {
    color: #666;
    font-style: italic;
  }
</style>
