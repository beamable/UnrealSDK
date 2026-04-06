<script lang="ts">
  import { onMount } from 'svelte'
  import { type ExtensionContext } from '@beamable/portal-toolkit'
  import { realmsGetConfigBasic, realmsPostConfigBasic, realmsGetCustomersBasic } from '@beamable/sdk/api'

  export let context: ExtensionContext

  // ── state ────────────────────────────────────────────────────────────────────
  let loading = true
  let error = ''
  let missingKeys: string[] = []

  let apiKey = ''
  let appName = ''
  let appVersion = ''

  // ── wizard state ─────────────────────────────────────────────────────
  // step 1 = enter API key, step 2 = pick app, step 3 = pick version
  let wizardStep = 1
  let setupApiKey = ''
  let wizardLoading = false
  let wizardError = ''
  let availableApps: any[] = []
  let selectedApp: any = null
  let availableVersions: any[] = []

  let appInfo: any = null
  let versionInfo: any = null

  let envSetupLoading = false
  let envSetupError = ''
  let envSetupSuccess = false

  const REQUIRED_ENV_KEYS = [
    'BEAMABLE_CUSTOMER_OVERRIDE',
    'BEAMABLE_REALM_OVERRIDE',
    'BEAMABLE_REALM_SECRET',
  ]

  // ── helpers ──────────────────────────────────────────────────────────────────
  function authHeader(key: string) {
    return key.toLowerCase().startsWith('token ') ? key : `token ${key}`
  }

  async function edgegapFetch(path: string, method = 'GET', body?: object) {
    const init: RequestInit = {
      method,
      headers: {
        authorization: authHeader(apiKey),
        accept: 'application/json',
        ...(body ? { 'content-type': 'application/json' } : {}),
      },
      ...(body ? { body: JSON.stringify(body) } : {}),
    }

    const response = await fetch(`https://api.edgegap.com${path}`, init)

    if (!response.ok) {
      let message = `Request failed (${response.status})`
      try {
        const payload = await response.json()
        message = payload?.message || payload?.error || message
      } catch (_) {}
      throw new Error(message)
    }

    return response.json()
  }

  function currentEnvMap(envs: { key: string; value: string }[] = []) {
    return Object.fromEntries(envs.map(e => [e.key, e.value]))
  }

  // ── data loading ─────────────────────────────────────────────────────────────
  async function loadConfig() {
    loading = true
    error = ''
    missingKeys = []
    appInfo = null
    versionInfo = null

    try {
      const beamInstance = await context.beam
      const response = await realmsGetConfigBasic(beamInstance.requester)
      const cfg = response.body.config

      const foundKey     = cfg['edgegap_integration|app_key']     ?? ''
      const foundAppName = cfg['edgegap_integration|app_name']    ?? ''
      const foundVersion = cfg['edgegap_integration|app_version'] ?? ''

      if (!foundKey)     missingKeys.push('edgegap_integration|app_key')
      if (!foundAppName) missingKeys.push('edgegap_integration|app_name')
      if (!foundVersion) missingKeys.push('edgegap_integration|app_version')

      // Pre-populate API key input if it was already in realm config
      setupApiKey = foundKey

      if (missingKeys.length > 0) return

      apiKey     = foundKey
      appName    = foundAppName
      appVersion = foundVersion

      const [app, version] = await Promise.all([
        edgegapFetch(`/v1/app/${encodeURIComponent(appName)}`),
        edgegapFetch(`/v1/app/${encodeURIComponent(appName)}/version/${encodeURIComponent(appVersion)}`),
      ])

      appInfo     = app
      versionInfo = version
    } catch (err: any) {
      error = err?.message || 'Failed to load configuration.'
    } finally {
      loading = false
    }
  }

  // ── wizard steps ─────────────────────────────────────────────────────────────
  async function wizardConnectKey() {
    if (!setupApiKey.trim()) { wizardError = 'API Key is required.'; return }
    wizardLoading = true
    wizardError   = ''
    apiKey = setupApiKey.trim()
    try {
      const data = await edgegapFetch('/v1/apps')
      availableApps = data?.applications ?? []
      if (availableApps.length === 0) wizardError = 'No applications found for this API key.'
      else wizardStep = 2
    } catch (err: any) {
      wizardError = err?.message || 'Failed to fetch applications.'
      apiKey = ''
    } finally {
      wizardLoading = false
    }
  }

  async function wizardSelectApp(app: any) {
    selectedApp   = app
    wizardLoading = true
    wizardError   = ''
    try {
      const data = await edgegapFetch(`/v1/app/${encodeURIComponent(app.name)}/versions`)
      availableVersions = data?.versions ?? []
      if (availableVersions.length === 0) wizardError = 'No versions found for this application.'
      else wizardStep = 3
    } catch (err: any) {
      wizardError = err?.message || 'Failed to fetch versions.'
    } finally {
      wizardLoading = false
    }
  }

  async function wizardSelectVersion(version: any) {
    wizardLoading = true
    wizardError   = ''
    try {
      const beamInstance = await context.beam
      await realmsPostConfigBasic(beamInstance.requester, {
        upserts: {
          'edgegap_integration|app_key':     setupApiKey.trim(),
          'edgegap_integration|app_name':    selectedApp.name,
          'edgegap_integration|app_version': version.name,
        },
      })
      await loadConfig()
    } catch (err: any) {
      wizardError = err?.message || 'Failed to save configuration.'
    } finally {
      wizardLoading = false
    }
  }

  // ── env var setup ─────────────────────────────────────────────────────────────
  async function setupEnvVars() {
    envSetupLoading = true
    envSetupError   = ''
    envSetupSuccess = false

    try {
      const beamInstance = await context.beam
      const cid = beamInstance.cid
      const pid = beamInstance.pid

      const customersResponse = await realmsGetCustomersBasic(beamInstance.requester)
      const customers = customersResponse.body.result ?? []
      const customer = customers.find((c: any) => String(c.cid) === String(cid))
      if (!customer) throw new Error(`No customer found matching cid "${cid}".`)
      const project = customer.projects.find((p: any) => p.name === pid)
      if (!project?.secret) throw new Error(`No project secret found for pid "${pid}".`)

      await edgegapFetch(
        `/v1/app/${encodeURIComponent(appName)}/version/${encodeURIComponent(appVersion)}`,
        'PATCH',
        {
          envs: [
            { key: 'BEAMABLE_CUSTOMER_OVERRIDE', value: String(cid),    is_secret: false },
            { key: 'BEAMABLE_REALM_OVERRIDE',    value: String(pid),    is_secret: false },
            { key: 'BEAMABLE_REALM_SECRET',      value: project.secret, is_secret: true  },
          ],
        },
      )

      envSetupSuccess = true

      // Refresh version info to reflect the new envs
      versionInfo = await edgegapFetch(
        `/v1/app/${encodeURIComponent(appName)}/version/${encodeURIComponent(appVersion)}`
      )
    } catch (err: any) {
      envSetupError = err?.message || 'Failed to set environment variables.'
    } finally {
      envSetupLoading = false
    }
  }

  onMount(() => {
    loadConfig()
  })
</script>

<!-- ── Loading ────────────────────────────────────────────────────────────────── -->
{#if loading}
  <beam-card>
    <beam-card-title>Edgegap Overview</beam-card-title>
    <beam-progress-linear indeterminate></beam-progress-linear>
  </beam-card>

<!-- ── Missing config / wizard ─────────────────────────────────────────────── -->
{:else if missingKeys.length > 0}
  <beam-card>
    <beam-card-title>Edgegap Overview</beam-card-title>

    <beam-card class="section" {...{outlined: ""}}>

      <!-- Step 1: API Key -->
      {#if wizardStep === 1}
        <beam-card-subtitle>Step 1 — Connect with API Key</beam-card-subtitle>
        <div class="section-content">
          <div class="field-group">
            <div class="field-label-row">
              <label class="field-label" for="setup-api-key">API Key</label>
              <a class="field-link" href="https://app.edgegap.com/?oneClick=true" target="_blank" rel="noopener noreferrer">Get API Token ↗</a>
            </div>
            <input
              id="setup-api-key"
              class="text-field"
              type="text"
              value={setupApiKey}
              on:input={(e) => { setupApiKey = e.currentTarget.value; wizardError = '' }}
              placeholder="token xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx"
            />
          </div>
          {#if wizardError}
            <beam-alert type="error" dense class="mt">{wizardError}</beam-alert>
          {/if}
        </div>
        <beam-card-actions>
          <beam-btn
            role="button" tabindex="0" color="primary"
            on:click={wizardConnectKey}
            on:keydown={(e) => (e.key === 'Enter' || e.key === ' ') && wizardConnectKey()}
            loading={wizardLoading ? true : null}
            disabled={wizardLoading ? true : null}
          >{wizardLoading ? 'Connecting…' : 'Connect'}</beam-btn>
        </beam-card-actions>

      <!-- Step 2: Pick Application -->
      {:else if wizardStep === 2}
        <beam-card-subtitle>Step 2 — Select Application</beam-card-subtitle>
        <div class="section-content">
          {#if wizardLoading}
            <beam-progress-linear indeterminate></beam-progress-linear>
          {:else}
            <div class="pick-list">
              {#each availableApps as app}
                <button
                  class="pick-item"
                  on:click={() => wizardSelectApp(app)}
                >
                  <span class="pick-name">{app.name}</span>
                  <beam-chip x-small color={app.is_active ? 'success' : 'error'}>
                    {app.is_active ? 'Active' : 'Inactive'}
                  </beam-chip>
                </button>
              {/each}
            </div>
            {#if wizardError}
              <beam-alert type="error" dense class="mt">{wizardError}</beam-alert>
            {/if}
          {/if}
        </div>
        <beam-card-actions>
          <beam-btn role="button" tabindex="0" outlined
            on:click={() => { wizardStep = 1; wizardError = '' }}
            on:keydown={(e) => (e.key === 'Enter' || e.key === ' ') && (wizardStep = 1)}
          >Back</beam-btn>
        </beam-card-actions>

      <!-- Step 3: Pick Version -->
      {:else if wizardStep === 3}
        <beam-card-subtitle>Step 3 — Select Version for “{selectedApp?.name}”</beam-card-subtitle>
        <div class="section-content">
          {#if wizardLoading}
            <beam-progress-linear indeterminate></beam-progress-linear>
          {:else}
            <div class="pick-list">
              {#each availableVersions as version}
                <button
                  class="pick-item"
                  on:click={() => wizardSelectVersion(version)}
                >
                  <span class="pick-name">{version.name}</span>
                  <span class="pick-meta">{version.docker_image}:{version.docker_tag}</span>
                  <beam-chip x-small color={version.is_active ? 'success' : 'error'}>
                    {version.is_active ? 'Active' : 'Inactive'}
                  </beam-chip>
                </button>
              {/each}
            </div>
            {#if wizardError}
              <beam-alert type="error" dense class="mt">{wizardError}</beam-alert>
            {/if}
          {/if}
        </div>
        <beam-card-actions>
          <beam-btn role="button" tabindex="0" outlined
            on:click={() => { wizardStep = 2; wizardError = '' }}
            on:keydown={(e) => (e.key === 'Enter' || e.key === ' ') && (wizardStep = 2)}
          >Back</beam-btn>
        </beam-card-actions>
      {/if}

    </beam-card>

    <beam-card>
      <beam-card-actions>
        <beam-btn href="https://docs.edgegap.com/unreal-engine" target="_blank"  style="margin-right: 0.5rem;">
          EdgeGap Unreal Setup Guide
        </beam-btn>

        <beam-btn href="https://docs.edgegap.com/api" target="_blank">
          EdgeGap API Reference
        </beam-btn>
      </beam-card-actions>
    </beam-card>
  </beam-card>

<!-- ── Error ──────────────────────────────────────────────────────────────────── -->
{:else if error}
  <beam-card>
    <beam-card-title>Edgegap Overview</beam-card-title>
    <beam-card-text>
      <beam-alert type="error" dense>{error}</beam-alert>
    </beam-card-text>
    <beam-card-actions>
      <beam-btn
        role="button"
        tabindex="0"
        on:click={loadConfig}
        on:keydown={(e) => (e.key === 'Enter' || e.key === ' ') && loadConfig()}
      >Retry</beam-btn>
    </beam-card-actions>
  </beam-card>

<!-- ── Loaded ────────────────────────────────────────────────────────────────── -->
{:else if appInfo && versionInfo}
  {@const envMap = currentEnvMap(versionInfo.envs)}

  <beam-card>
    <beam-card-title>Edgegap Overview</beam-card-title>

    <!-- Application -->
    <beam-card class="section" {...{outlined: ""}}>
      <beam-card-subtitle>Application</beam-card-subtitle>
      <div class="section-content">
        <div class="detail-row">
          <span class="detail-label">Name</span>
          <span class="detail-value">{appInfo.name}</span>
        </div>
        <div class="detail-row">
          <span class="detail-label">Status</span>
          <beam-chip small color={appInfo.is_active ? 'success' : 'error'}>
            {appInfo.is_active ? 'Active' : 'Inactive'}
          </beam-chip>
        </div>
        {#if appInfo.last_updated}
          <div class="detail-row">
            <span class="detail-label">Last Updated</span>
            <span class="detail-value">{appInfo.last_updated}</span>
          </div>
        {/if}
      </div>
    </beam-card>

    <!-- Version -->
    <beam-card class="section" {...{outlined: ""}}>
      <beam-card-subtitle>Version: {versionInfo.name}</beam-card-subtitle>
      <div class="section-content">
        <div class="detail-row">
          <span class="detail-label">Status</span>
          <beam-chip small color={versionInfo.is_active ? 'success' : 'error'}>
            {versionInfo.is_active ? 'Active' : 'Inactive'}
          </beam-chip>
        </div>
        <div class="detail-row">
          <span class="detail-label">Image</span>
          <span class="detail-value detail-mono">{versionInfo.docker_image}:{versionInfo.docker_tag}</span>
        </div>
        {#if versionInfo.req_cpu != null}
          <div class="detail-row">
            <span class="detail-label">CPU / Memory</span>
            <span class="detail-value">{versionInfo.req_cpu} vCPU units / {versionInfo.req_memory} MB</span>
          </div>
        {/if}
      </div>

      <!-- Beamable env var status -->
      <beam-card-subtitle>Beamable Environment Variables</beam-card-subtitle>
      <div class="section-content">
        {#each REQUIRED_ENV_KEYS as envKey}
          {@const isSet = envKey in envMap}
          <div class="detail-row">
            <code class="env-key">{envKey}</code>
            <beam-chip x-small color={isSet ? 'success' : 'warning'}>
              {isSet ? 'Set' : 'Missing'}
            </beam-chip>
          </div>
        {/each}
      </div>
    </beam-card>

    <!-- Env var setup -->
    {#if REQUIRED_ENV_KEYS.some(k => !(k in envMap))}
    <beam-card class="section" {...{outlined: ""}}>
      <beam-card-subtitle>Setup Beamable Environment Variables</beam-card-subtitle>
      <div class="section-content">
        <p class="setup-description">
          Sets <code>BEAMABLE_CUSTOMER_OVERRIDE</code>, <code>BEAMABLE_REALM_OVERRIDE</code>, and
          <code>BEAMABLE_REALM_SECRET</code> on version <strong>{versionInfo.name}</strong>.
          CID, PID, and realm secret are read from your current realm automatically.
        </p>

        {#if envSetupError}
          <beam-alert type="error" dense class="mt">{envSetupError}</beam-alert>
        {/if}
        {#if envSetupSuccess}
          <beam-alert type="success" dense class="mt">Environment variables updated successfully.</beam-alert>
        {/if}
      </div>

      <beam-card-actions>
        <beam-btn
          role="button"
          tabindex="0"
          color="primary"
          on:click={setupEnvVars}
          on:keydown={(e) => (e.key === 'Enter' || e.key === ' ') && setupEnvVars()}
          loading={envSetupLoading ? true : null}
          disabled={envSetupLoading ? true : null}
        >
          {envSetupLoading ? 'Applying…' : 'Apply Env Variables'}
        </beam-btn>
        <beam-btn
          role="button"
          tabindex="0"
          outlined
          on:click={loadConfig}
          on:keydown={(e) => (e.key === 'Enter' || e.key === ' ') && !envSetupLoading && loadConfig()}
          disabled={envSetupLoading ? true : null}
        >
          Refresh
        </beam-btn>
      </beam-card-actions>
    </beam-card>
    {/if}
  </beam-card>
{/if}

<style>
  .section {
    display: block;
    margin: 0.75rem 0.5rem;
  }

  .section-content {
    padding: 0 0.75rem 0.6rem;
  }

  .detail-row {
    display: flex;
    justify-content: space-between;
    align-items: center;
    gap: 0.5rem;
    padding: 0.15rem 0;
    font-size: 0.82rem;
  }

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

  .env-key {
    font-family: monospace;
    font-size: 0.78rem;
    opacity: 0.75;
  }

  .setup-description {
    font-size: 0.85rem;
    opacity: 0.8;
    margin: 0 0 0.75rem;
    line-height: 1.4;
  }

  .link-group {
    display: flex;
    flex-wrap: wrap;
    gap: 0.5rem;
    margin-top: 0.75rem;
  }

  .link-group a {
    text-decoration: none;
  }

  .mt {
    margin-top: 0.6rem;
  }

  .pick-list {
    display: flex;
    flex-direction: column;
    gap: 0.4rem;
  }

  .pick-item {
    display: flex;
    align-items: center;
    gap: 0.6rem;
    width: 100%;
    padding: 0.55rem 0.75rem;
    background: rgba(255, 255, 255, 0.05);
    border: 1px solid rgba(255, 255, 255, 0.12);
    border-radius: 4px;
    color: inherit;
    font-family: inherit;
    font-size: 0.85rem;
    text-align: left;
    cursor: pointer;
    transition: background 0.15s, border-color 0.15s;
  }

  .pick-item:hover {
    background: rgba(255, 255, 255, 0.1);
    border-color: rgba(255, 255, 255, 0.28);
  }

  .pick-name {
    flex: 1;
    font-weight: 500;
  }

  .pick-meta {
    font-family: monospace;
    font-size: 0.75rem;
    opacity: 0.5;
  }

  .field-group {
    margin-bottom: 0.75rem;
  }

  .field-row {
    display: flex;
    gap: 0.6rem;
    align-items: flex-start;
  }

  .field-row .field-group {
    min-width: 0;
  }

  .field-grow {
    flex: 1;
  }

  .field-label-row {
    display: flex;
    justify-content: space-between;
    align-items: baseline;
    margin-bottom: 0.3rem;
  }

  .field-link {
    font-size: 0.72rem;
    opacity: 0.65;
    text-decoration: none;
    color: inherit;
    transition: opacity 0.15s;
  }

  .field-link:hover {
    opacity: 1;
    text-decoration: underline;
  }

  .field-label {
    display: block;
    font-size: 0.72rem;
    opacity: 0.55;
    text-transform: uppercase;
    letter-spacing: 0.06em;
  }

  .text-field {
    width: 100%;
    background: rgba(255, 255, 255, 0.06);
    border: 1px solid rgba(255, 255, 255, 0.18);
    border-radius: 4px;
    color: inherit;
    font-size: 0.85rem;
    padding: 0.45rem 0.7rem;
    box-sizing: border-box;
    outline: none;
    font-family: inherit;
    transition: border-color 0.15s;
  }

  .text-field:focus {
    border-color: rgba(255, 255, 255, 0.45);
  }

  .text-field::placeholder {
    opacity: 0.35;
  }
</style>
