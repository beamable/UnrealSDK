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
    <p class="placeholder">Loading servers...</p>
  {/if}

  {#if error}
    <p class="error">{error}</p>
  {/if}

  {#if deployments.length > 0}
    <div class="table-wrap">
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
                  role="button"
                  tabindex="0"
                >
                  Check More Info
                </beam-btn>
              </td>
            </tr>
          {/each}
        </tbody>
      </table>
    </div>

    {#if selectedRequestId}
      <div class="details-panel">
        <div class="details-header">
          <h4>Server Details</h4>
          <span class="request-id-badge">{selectedRequestId}</span>
        </div>
        {#if deploymentDetails[selectedRequestId]}
          {@const d = deploymentDetails[selectedRequestId]}
          <div class="details-grid">
            <div class="detail-section">
              <h5>Status</h5>
              <div class="detail-row">
                <span class="detail-label">Running</span>
                <span class="status-badge {d.running ? 'status-running' : 'status-stopped'}">
                  {d.running ? 'Running' : 'Stopped'}
                </span>
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
                  <span class="detail-value error-text">{d.error_detail || 'Unknown error'}</span>
                </div>
              {/if}
            </div>

            <div class="detail-section">
              <h5>Application</h5>
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

            <div class="detail-section">
              <h5>Timing</h5>
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

            <div class="detail-section">
              <h5>Capacity</h5>
              <div class="detail-row">
                <span class="detail-label">Sockets Used</span>
                <span class="detail-value">{d.sockets_usage ?? 'N/A'} / {d.sockets ?? 'N/A'}</span>
              </div>
            </div>
          </div>

          {#if d.ports && Object.keys(d.ports).length > 0}
            <div class="detail-section detail-section-full">
              <h5>Ports</h5>
              <table class="inner-table">
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
                      <td><span class="protocol-badge">{port.protocol}</span></td>
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
            </div>
          {/if}

          {#if d.location}
            <div class="detail-section detail-section-full">
              <h5>Location</h5>
              <div class="location-info">
                <span>{[d.location.city, d.location.administrative_division, d.location.country].filter(Boolean).join(', ')}</span>
                <span class="detail-muted">{[d.location.continent, d.location.timezone].filter(Boolean).join(' · ')}</span>
              </div>
            </div>
          {/if}

          {#if d.sessions && d.sessions.length > 0}
            <div class="detail-section detail-section-full">
              <h5>Sessions ({d.sessions.length})</h5>
              <table class="inner-table">
                <thead>
                  <tr>
                    <th>Session ID</th>
                    <th>Status</th>
                    <th>Ready</th>
                    <th>Linked</th>
                    <th>Kind</th>
                    <th>Users</th>
                  </tr>
                </thead>
                <tbody>
                  {#each d.sessions as session}
                    <tr>
                      <td class="detail-mono">{session.session_id}</td>
                      <td>{session.status}</td>
                      <td>{session.ready ? 'Yes' : 'No'}</td>
                      <td>{session.linked ? 'Yes' : 'No'}</td>
                      <td>{session.kind}</td>
                      <td>{session.user_count}</td>
                    </tr>
                  {/each}
                </tbody>
              </table>
            </div>
          {/if}

          {#if d.tags && d.tags.length > 0}
            <div class="detail-section detail-section-full">
              <h5>Tags</h5>
              <div class="tags-list">
                {#each d.tags as tag}
                  <span class="tag-pill">{tag}</span>
                {/each}
              </div>
            </div>
          {/if}
        {:else}
          <p class="placeholder">No additional details available for this server.</p>
        {/if}
      </div>
    {/if}
  {:else if !loading}
    <p class="placeholder">Load servers to see running instances and statuses.</p>
  {/if}
</beam-card>

<style>
  .table-wrap {
    width: 100%;
    overflow-x: auto;
    margin-top: 0.75rem;
  }

  table {
    width: 100%;
    border-collapse: collapse;
  }

  th,
  td {
    padding: 0.6rem 0.5rem;
    border-bottom: 1px solid #e5e7eb;
    text-align: left;
    font-size: 0.9rem;
    vertical-align: top;
  }

  .details-panel {
    margin-top: 0.9rem;
    border: 1px solid rgba(255,255,255,0.1);
    border-radius: 8px;
    padding: 0.8rem;
    background: rgba(255,255,255,0.05);
  }

  .error {
    color: #b00020;
    margin-top: 0.5rem;
    font-size: 0.9rem;
  }

  .placeholder {
    color: rgba(255,255,255,0.4);
    font-style: italic;
    margin-top: 0.75rem;
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

  .request-id-badge {
    font-family: monospace;
    font-size: 0.78rem;
    background: rgba(100,160,255,0.15);
    color: #7eb8ff;
    padding: 0.15rem 0.5rem;
    border-radius: 4px;
  }

  .details-grid {
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(190px, 1fr));
    gap: 0.6rem;
    margin-bottom: 0.6rem;
  }

  .detail-section {
    background: rgba(255,255,255,0.07);
    border: 1px solid rgba(255,255,255,0.1);
    border-radius: 6px;
    padding: 0.55rem 0.7rem;
  }

  .detail-section-full {
    margin-top: 0.5rem;
  }

  .detail-section h5 {
    margin: 0 0 0.35rem 0;
    font-size: 0.7rem;
    text-transform: uppercase;
    letter-spacing: 0.06em;
    color: rgba(255,255,255,0.45);
  }

  .detail-row {
    display: flex;
    justify-content: space-between;
    align-items: baseline;
    gap: 0.5rem;
    padding: 0.12rem 0;
    font-size: 0.82rem;
  }

  .detail-label {
    color: rgba(255,255,255,0.5);
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

  .status-badge {
    font-size: 0.72rem;
    padding: 0.1rem 0.45rem;
    border-radius: 999px;
    font-weight: 600;
  }

  .status-running {
    background: #dcfce7;
    color: #15803d;
  }

  .status-stopped {
    background: #fee2e2;
    color: #b91c1c;
  }

  .error-text {
    color: #b00020;
  }

  .inner-table {
    width: 100%;
    border-collapse: collapse;
    font-size: 0.82rem;
  }

  .inner-table th,
  .inner-table td {
    padding: 0.3rem 0.45rem;
    border-bottom: 1px solid rgba(255,255,255,0.08);
    text-align: left;
  }

  .inner-table th {
    font-weight: 600;
    color: rgba(255,255,255,0.45);
    font-size: 0.72rem;
    text-transform: uppercase;
    letter-spacing: 0.05em;
  }

  .protocol-badge {
    font-size: 0.68rem;
    padding: 0.1rem 0.35rem;
    border-radius: 4px;
    background: rgba(255,255,255,0.12);
    color: rgba(255,255,255,0.85);
    font-weight: 700;
    text-transform: uppercase;
  }

  .location-info {
    display: flex;
    flex-direction: column;
    gap: 0.15rem;
    font-size: 0.85rem;
  }

  .detail-muted {
    color: rgba(255,255,255,0.35);
    font-size: 0.78rem;
  }

  .tags-list {
    display: flex;
    flex-wrap: wrap;
    gap: 0.35rem;
  }

  .tag-pill {
    font-size: 0.72rem;
    padding: 0.15rem 0.5rem;
    background: rgba(255,255,255,0.12);
    border-radius: 999px;
    color: rgba(255,255,255,0.8);
  }

  .details-panel a {
    color: #7eb8ff;
    text-decoration: none;
  }

  .details-panel a:hover {
    text-decoration: underline;
  }
</style>