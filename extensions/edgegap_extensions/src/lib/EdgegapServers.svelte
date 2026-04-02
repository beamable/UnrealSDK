<script>
  import { onMount, onDestroy } from 'svelte'
  import { Beam, Context } from '../store.js'
  // import { realmsGetConfigBasic } from 'beamable-sdk/api'

  let loading = false
  let error = ''

  let apiToken = ''
  let deployments = []
  let deploymentDetails = {}
  let selectedRequestId = null

  let refreshInterval = null

  async function getApiToken() {
  
    // const response = await realmsGetConfigBasic($Beam)
    
    // console.log('Realms config response:', response);

    return "";
  }

  async function authHeaderValue() {

    if (!apiToken) {
        apiToken = await getApiToken()
    }
    return apiToken.trim().toLowerCase().startsWith('token ')
      ? apiToken.trim()
      : `token ${apiToken.trim()}`
  }

  async function edgegapGet(path) {
    const response = await fetch(`https://api.edgegap.com${path}`, {
      method: 'GET',
      headers: {
        authorization: await authHeaderValue(),
        accept: 'application/json'
      }
    })

    if (!response.ok) {
      let message = `Request failed (${response.status})`
      try {
        const payload = await response.json()
        message = payload?.message || payload?.error || message
      } catch (_) {
        // Keep fallback message when response body is not JSON.
      }
      throw new Error(message)
    }

    return response.json()
  }

  async function loadDeployments() {
    loading = true
    error = ''

    try {
      if (!apiToken.trim()) {
        apiToken = await getApiToken()
      }

      const listResponse = await edgegapGet('/v1/deployments')
      const newDeployments = Array.isArray(listResponse?.data) ? listResponse.data : []

      const newDetails = {}
      await Promise.all(
        newDeployments.map(async (deployment) => {
          if (!deployment?.request_id) return

          try {
            newDetails[deployment.request_id] = await edgegapGet(`/v1/status/${deployment.request_id}`)
          } catch (_) {
            newDetails[deployment.request_id] = null
          }
        })
      )

      deployments = newDeployments
      deploymentDetails = newDetails

      // If the selected deployment no longer exists, clear the selection
      if (selectedRequestId && !newDetails.hasOwnProperty(selectedRequestId)) {
        selectedRequestId = null
      }
    } catch (err) {
      console.error('Failed to load Edgegap deployments:', err)
      error = err?.message || 'Failed to load deployments.'
    } finally {
      loading = false
    }
  }

  onMount(() => {
    loadDeployments()
    refreshInterval = setInterval(loadDeployments, 10000)
  })

  onDestroy(() => {
    clearInterval(refreshInterval)
  })

  function showMoreInfo(requestId) {
    selectedRequestId = selectedRequestId === requestId ? null : requestId
  }

  function runningLabel(deployment) {
    const details = deploymentDetails[deployment.request_id]
    if (details?.running === true) return 'Running'
    if (details?.running === false) return 'Stopped'
    if (deployment?.ready === true) return 'Running'
    if (deployment?.ready === false) return 'Starting'
    return 'Unknown'
  }

  function stateLabel(deployment) {
    const details = deploymentDetails[deployment.request_id]
    return details?.current_status || details?.last_status || (deployment?.ready ? 'Status.READY' : 'Status.UNKNOWN')
  }
</script>

<beam-card>
  <beam-card-title>Edgegap Dedicated Servers</beam-card-title>

  {#if loading && deployments.length === 0}
    <beam-progress-linear indeterminate></beam-progress-linear>
  {/if}

  {#if error}
    <beam-alert type="error" dense>{error}</beam-alert>
  {/if}

  {#if deployments.length > 0}
    <beam-simple-table>
      <table>
        <thead>
          <tr>
            <th>Request ID</th>
            <th>FQDN</th>
            <th>Running</th>
            <th>State</th>
            <th>Action</th>
          </tr>
        </thead>
        <tbody>
          {#each deployments as deployment}
            <tr>
              <td>{deployment.request_id}</td>
              <td>{deployment.fqdn || 'N/A'}</td>
              <td>{runningLabel(deployment)}</td>
              <td>{stateLabel(deployment)}</td>
              <td>
                <beam-btn
                  on:click={() => showMoreInfo(deployment.request_id)}
                  on:keydown={(event) => (event.key === 'Enter' || event.key === ' ') && showMoreInfo(deployment.request_id)}
                >
                  Check More Info
                </beam-btn>
              </td>
            </tr>
          {/each}
        </tbody>
      </table>
    </beam-simple-table>

    {#if selectedRequestId}
      <beam-card outlined class="details-panel">
        <beam-card-text>
          <div class="details-header">
            <h4>Server Details</h4>
            <beam-chip small outlined>{selectedRequestId}</beam-chip>
          </div>
          {#if deploymentDetails[selectedRequestId]}
            {@const d = deploymentDetails[selectedRequestId]}
            <div class="details-grid">
              <beam-card outlined class="section-card">
                <beam-card-subtitle>Status</beam-card-subtitle>
                <div class="section-content">
                  <div class="detail-row">
                    <span class="detail-label">Running</span>
                    <beam-chip small color={d.running ? 'success' : 'error'}>
                      {d.running ? 'Running' : 'Stopped'}
                    </beam-chip>
                  </div>
                  <div class="detail-row">
                    <span class="detail-label">Current</span>
                    <span class="detail-value">{d.current_status || 'N/A'}</span>
                  </div>
                  <div class="detail-row">
                    <span class="detail-label">Last</span>
                    <span class="detail-value">{d.last_status || 'N/A'}</span>
                  </div>
                  {#if d.error}
                    <div class="detail-row">
                      <span class="detail-label">Error</span>
                      <span class="detail-value">{d.error_detail || 'Unknown error'}</span>
                    </div>
                  {/if}
                </div>
              </beam-card>

              <beam-card outlined class="section-card">
                <beam-card-subtitle>Application</beam-card-subtitle>
                <div class="section-content">
                  <div class="detail-row">
                    <span class="detail-label">App</span>
                    <span class="detail-value">{d.app_name || 'N/A'}</span>
                  </div>
                  <div class="detail-row">
                    <span class="detail-label">Version</span>
                    <span class="detail-value">{d.app_version || 'N/A'}</span>
                  </div>
                  <div class="detail-row">
                    <span class="detail-label">FQDN</span>
                    <span class="detail-value detail-mono">{d.fqdn || 'N/A'}</span>
                  </div>
                  <div class="detail-row">
                    <span class="detail-label">Public IP</span>
                    <span class="detail-value detail-mono">{d.public_ip || 'N/A'}</span>
                  </div>
                </div>
              </beam-card>

              <beam-card outlined class="section-card">
                <beam-card-subtitle>Timing</beam-card-subtitle>
                <div class="section-content">
                  <div class="detail-row">
                    <span class="detail-label">Started</span>
                    <span class="detail-value">{d.start_time || 'N/A'}</span>
                  </div>
                  <div class="detail-row">
                    <span class="detail-label">Elapsed</span>
                    <span class="detail-value">{d.elapsed_time != null ? `${d.elapsed_time}s` : 'N/A'}</span>
                  </div>
                  <div class="detail-row">
                    <span class="detail-label">Max Duration</span>
                    <span class="detail-value">{d.max_duration != null ? `${d.max_duration}h` : 'N/A'}</span>
                  </div>
                  <div class="detail-row">
                    <span class="detail-label">Whitelisting</span>
                    <span class="detail-value">{d.whitelisting_active ? 'Active' : 'Inactive'}</span>
                  </div>
                </div>
              </beam-card>

              <beam-card outlined class="section-card">
                <beam-card-subtitle>Capacity</beam-card-subtitle>
                <div class="section-content">
                  <div class="detail-row">
                    <span class="detail-label">Sockets Used</span>
                    <span class="detail-value">{d.sockets_usage ?? 'N/A'} / {d.sockets ?? 'N/A'}</span>
                  </div>
                </div>
              </beam-card>
            </div>

            {#if d.ports && Object.keys(d.ports).length > 0}
              <beam-card outlined class="detail-section-full">
                <beam-card-subtitle>Ports</beam-card-subtitle>
                <beam-simple-table dense>
                  <table>
                    <thead>
                      <tr>
                        <th>Name</th>
                        <th>Internal</th>
                        <th>External</th>
                        <th>Protocol</th>
                        <th>Link</th>
                      </tr>
                    </thead>
                    <tbody>
                      {#each Object.values(d.ports) as port}
                        <tr>
                          <td>{port.name}</td>
                          <td class="detail-mono">{port.internal}</td>
                          <td class="detail-mono">{port.external}</td>
                          <td><beam-chip x-small>{port.protocol}</beam-chip></td>
                          <td class="detail-mono">
                            {#if port.link}
                              <a href={port.link} target="_blank" rel="noopener noreferrer">{port.link}</a>
                            {:else}
                              N/A
                            {/if}
                          </td>
                        </tr>
                      {/each}
                    </tbody>
                  </table>
                </beam-simple-table>
              </beam-card>
            {/if}

            {#if d.location}
              <beam-card outlined class="detail-section-full">
                <beam-card-subtitle>Location</beam-card-subtitle>
                <div class="section-content">
                  <div class="location-info">
                    <span>{[d.location.city, d.location.administrative_division, d.location.country].filter(Boolean).join(', ')}</span>
                    <span class="detail-muted">{[d.location.continent, d.location.timezone].filter(Boolean).join(' · ')}</span>
                  </div>
                </div>
              </beam-card>
            {/if}

            {#if d.sessions && d.sessions.length > 0}
              <beam-card outlined class="detail-section-full">
                <beam-card-subtitle>Sessions ({d.sessions.length})</beam-card-subtitle>
                <beam-data-table
                  headers={[
                    { text: 'Session ID', value: 'session_id' },
                    { text: 'Status',     value: 'status' },
                    { text: 'Ready',      value: 'ready' },
                    { text: 'Linked',     value: 'linked' },
                    { text: 'Kind',       value: 'kind' },
                    { text: 'Users',      value: 'user_count' },
                  ]}
                  items={d.sessions.map(s => ({
                    session_id: s.session_id,
                    status:     s.status,
                    ready:      s.ready ? 'Yes' : 'No',
                    linked:     s.linked ? 'Yes' : 'No',
                    kind:       s.kind,
                    user_count: s.user_count,
                  }))}
                  dense
                  hide-default-footer
                ></beam-data-table>
              </beam-card>
            {/if}

            {#if d.tags && d.tags.length > 0}
              <beam-card outlined class="detail-section-full">
                <beam-card-subtitle>Tags</beam-card-subtitle>
                <div class="section-content">
                  <div class="tags-list">
                    {#each d.tags as tag}
                      <beam-chip small>{tag}</beam-chip>
                    {/each}
                  </div>
                </div>
              </beam-card>
            {/if}
          {:else}
            <beam-alert type="info" dense outlined>No additional details available for this server.</beam-alert>
          {/if}
        </beam-card-text>
      </beam-card>
    {/if}
  {:else if !loading}
    <beam-alert type="info" dense outlined>Load servers to see running instances and statuses.</beam-alert>
  {/if}
</beam-card>

<style>
  .details-panel {
    margin-top: 0.9rem;
  }

  .details-header {
    display: flex;
    align-items: center;
    gap: 0.5rem;
    margin-bottom: 0.75rem;
  }

  .details-header h4 {
    margin: 0;
  }

  .details-grid {
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(190px, 1fr));
    gap: 0.6rem;
    margin-bottom: 0.6rem;
  }

  /* force custom elements to behave as block for CSS grid */
  .details-grid beam-card,
  .section-card {
    display: block;
  }

  /* tint gives contrast against the outer panel in both light and dark themes */
  .section-card {
    background: color-mix(in srgb, currentColor 6%, transparent) !important;
  }

  .section-content {
    padding: 0 0.7rem 0.6rem;
  }

  .detail-section-full {
    margin-top: 0.5rem;
    display: block;
  }

  .detail-row {
    display: flex;
    justify-content: space-between;
    align-items: baseline;
    gap: 0.5rem;
    padding: 0.12rem 0;
    font-size: 0.82rem;
  }

  /* opacity-based so it works in both light and dark themes */
  .detail-label {
    opacity: 0.6;
    white-space: nowrap;
    flex-shrink: 0;
  }

  .detail-value {
    font-weight: 500;
    text-align: right;
    word-break: break-all;
  }

  .detail-mono {
    font-family: monospace;
    font-size: 0.8rem;
  }

  /* table cell alignment for beam-simple-table */
  table {
    width: 100%;
    border-collapse: collapse;
  }

  th,
  td {
    padding: 0.5rem 0.6rem;
    text-align: left;
    vertical-align: middle;
    font-size: 0.85rem;
  }

  th {
    font-weight: 600;
    font-size: 0.75rem;
    text-transform: uppercase;
    letter-spacing: 0.05em;
    opacity: 0.55;
  }

  .location-info {
    display: flex;
    flex-direction: column;
    gap: 0.15rem;
    font-size: 0.85rem;
  }

  .detail-muted {
    opacity: 0.45;
    font-size: 0.78rem;
  }

  .tags-list {
    display: flex;
    flex-wrap: wrap;
    gap: 0.35rem;
  }
</style>