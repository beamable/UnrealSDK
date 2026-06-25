import { useEffect, useState, useCallback, useMemo } from 'react'
import { type ExtensionContext } from '@beamable/portal-toolkit'
import {
  useBeam,
  BeamPage,
  BeamPageHeader,
  BeamCard,
  BeamButton,
  BeamBadge,
  BeamSpinner,
  BeamInput,
  BeamTextarea,
  BeamTable,
  BeamColumn,
  BeamTag,
  BeamCheckbox,
} from '@beamable/portal-toolkit/react'
import { BeamFarmMsClient } from '../beamable/clients/BeamFarmMsClient'
import type {
  RegisteredPlayer,
  PushOffer,
  PushCampaignRequest,
} from '../beamable/clients/types'

interface AppProps {
  context: ExtensionContext
}

/** Aggregate of a bulk send across multiple players. */
interface BulkSendResult {
  playersAttempted: number
  playersOk: number
  devicesDelivered: number
  devicesFailed: number
  messages: string[]
}

/** One editable offer row in the structured editor. */
interface OfferRow {
  itemId: string
  value: string
  customData: string // free-form; serialized to a JSON string on send if non-empty
}

/** One editable campaignData key→value row. */
interface KvRow {
  key: string
  value: string
}

/**
 * Build a JSON object string from key→value rows, skipping rows with an empty key.
 * Returns '' when there are no usable rows so the field can stay omitted.
 */
function kvRowsToJson(rows: KvRow[]): string {
  const obj: Record<string, string> = {}
  let any = false
  for (const r of rows) {
    const k = r.key.trim()
    if (!k) continue
    obj[k] = r.value
    any = true
  }
  return any ? JSON.stringify(obj) : ''
}

function formatUnixSeconds(value: bigint | string): string {
  const seconds = Number(value)
  if (!seconds || Number.isNaN(seconds)) return '—'
  return new Date(seconds * 1000).toLocaleString()
}

export default function App({ context }: AppProps) {
  // Resolves context.beam into the SDK instance, re-rendering once it lands
  // (null until ready). Replaces the manual useState + context.beam.then effect.
  const beam = useBeam(context)

  // Roster state
  const [players, setPlayers] = useState<RegisteredPlayer[]>([])
  const [rosterLoading, setRosterLoading] = useState(false)
  const [rosterError, setRosterError] = useState<string | null>(null)
  const [rosterNote, setRosterNote] = useState<string | null>(null)

  // Selection state (keyed by stringified playerId — playerId is bigint|string)
  const [selected, setSelected] = useState<Set<string>>(new Set())

  // Send form state
  const [playerId, setPlayerId] = useState('') // optional ad-hoc single target
  const [title, setTitle] = useState('')
  const [body, setBody] = useState('')
  const [deepLink, setDeepLink] = useState('')
  const [sending, setSending] = useState(false)
  const [sendResult, setSendResult] = useState<BulkSendResult | null>(null)
  const [sendError, setSendError] = useState<string | null>(null)

  // --- Structured campaign editor (§3.3 Notification Intent Data) -----
  // All scalar fields below are optional: leaving them blank sends an "untracked" push
  // (no campaignId + nodeId → no funnel "Sent" event server-side).
  const [campaignId, setCampaignId] = useState('')
  const [nodeId, setNodeId] = useState('')
  const [accountId, setAccountId] = useState('')
  const [cidPid, setCidPid] = useState('')
  const [offers, setOffers] = useState<OfferRow[]>([])
  const [campaignData, setCampaignData] = useState<KvRow[]>([])

  const loadRoster = useCallback(async () => {
    if (!beam) return
    setRosterLoading(true)
    setRosterError(null)
    setRosterNote(null)
    try {
      const client = new BeamFarmMsClient(beam)
      const result = await client.listRegisteredPlayers()
      setPlayers(result.players ?? [])
      setRosterNote(result.message ?? null)
    } catch (err) {
      setRosterError(err instanceof Error ? err.message : String(err))
    } finally {
      setRosterLoading(false)
    }
  }, [beam])

  // Load the roster as soon as the Beam context is ready.
  useEffect(() => {
    if (beam) void loadRoster()
  }, [beam, loadRoster])

  // --- Selection helpers ---------------------------------------------
  const toggle = useCallback((id: string) => {
    setSelected((prev) => {
      const next = new Set(prev)
      if (next.has(id)) next.delete(id)
      else next.add(id)
      return next
    })
  }, [])

  const selectAll = useCallback(() => {
    setSelected(new Set(players.map((p) => String(p.playerId))))
  }, [players])

  const clearSelection = useCallback(() => setSelected(new Set()), [])

  // --- Offers editor helpers -----------------------------------------
  const addOffer = useCallback(
    () => setOffers((prev) => [...prev, { itemId: '', value: '', customData: '' }]),
    [],
  )
  const removeOffer = useCallback(
    (i: number) => setOffers((prev) => prev.filter((_, idx) => idx !== i)),
    [],
  )
  const updateOffer = useCallback(
    (i: number, field: keyof OfferRow, value: string) =>
      setOffers((prev) => prev.map((o, idx) => (idx === i ? { ...o, [field]: value } : o))),
    [],
  )

  // --- campaignData (key→value) editor helpers -----------------------
  const addKv = useCallback(
    () => setCampaignData((prev) => [...prev, { key: '', value: '' }]),
    [],
  )
  const removeKv = useCallback(
    (i: number) => setCampaignData((prev) => prev.filter((_, idx) => idx !== i)),
    [],
  )
  const updateKv = useCallback(
    (i: number, field: keyof KvRow, value: string) =>
      setCampaignData((prev) => prev.map((r, idx) => (idx === i ? { ...r, [field]: value } : r))),
    [],
  )

  // The set of player IDs a send will target: every checked row, plus the
  // optional manually-typed ID.
  const targets = useMemo(() => {
    const t = new Set(selected)
    if (playerId.trim()) t.add(playerId.trim())
    return t
  }, [selected, playerId])

  // Author-time validation: each offer's customData, when non-empty, must be valid
  // JSON (it is shipped verbatim as a JSON string). Returns the indices of offers
  // whose customData fails to parse so we can flag them inline and block the send.
  const invalidCustomDataIdx = useMemo(() => {
    const bad = new Set<number>()
    offers.forEach((o, i) => {
      const custom = o.customData.trim()
      if (!custom) return
      try {
        JSON.parse(custom)
      } catch {
        bad.add(i)
      }
    })
    return bad
  }, [offers])
  const hasInvalidCustomData = invalidCustomDataIdx.size > 0

  async function sendPush() {
    if (!beam) return
    if (targets.size === 0) {
      setSendError('Select at least one player (or type a player ID).')
      return
    }
    if (!title.trim() && !body.trim()) {
      setSendError('A title or body is required.')
      return
    }
    if (hasInvalidCustomData) {
      setSendError('One or more offers have invalid JSON in Custom data.')
      return
    }
    setSending(true)
    setSendError(null)
    setSendResult(null)

    const client = new BeamFarmMsClient(beam)

    // Build the §3.3 campaign request. Every field on PushCampaignRequest is required in the
    // generated type, so unset scalars travel as empty strings (the microservice treats empty
    // as unset via IsNullOrWhiteSpace). Each offer's free-form customData (a JSON object string)
    // and the campaignData key→value rows are serialized to JSON strings on the wire.
    const builtOffers: PushOffer[] = offers
      .filter((o) => o.itemId.trim() || o.value.trim() || o.customData.trim())
      .map((o) => ({
        itemId: o.itemId.trim(),
        value: o.value.trim(),
        customData: o.customData.trim(),
      }))
    const campaignDataJson = kvRowsToJson(campaignData)

    const campaignRequest: PushCampaignRequest = {
      title: title.trim(),
      body: body.trim(),
      deepLink: deepLink.trim(),
      campaignId: campaignId.trim(),
      nodeId: nodeId.trim(),
      gamerTag: '', // defaults to the target player id server-side
      accountId: accountId.trim(),
      cidPid: cidPid.trim(),
      offers: builtOffers,
      campaignData: campaignDataJson,
    }

    const outcomes = await Promise.all(
      [...targets].map((id) =>
        client
          .sendCampaignPushToPlayer({ playerId: id, request: campaignRequest })
          .then((r) => ({ id, r }))
          .catch((e) => ({ id, err: e instanceof Error ? e.message : String(e) })),
      ),
    )

    const agg: BulkSendResult = {
      playersAttempted: targets.size,
      playersOk: 0,
      devicesDelivered: 0,
      devicesFailed: 0,
      messages: [],
    }
    for (const o of outcomes) {
      if ('err' in o) {
        agg.messages.push(`${o.id}: ${o.err}`)
        continue
      }
      const r = o.r
      if (r.success) agg.playersOk++
      agg.devicesDelivered += r.succeeded
      agg.devicesFailed += r.failed
      for (const m of r.messages ?? []) agg.messages.push(`${o.id}: ${m}`)
    }

    setSendResult(agg)
    setSending(false)
    // Refresh the roster — a send may have pruned dead tokens.
    void loadRoster()
  }

  const targetCount = targets.size

  return (
    <BeamPage>
      <BeamPageHeader>Push Notifications</BeamPageHeader>

      {/* --- Send a push ------------------------------------------------ */}
      <BeamCard style={{ marginBottom: 20 }}>
        <h3 slot="header">Send a notification</h3>
        <div style={{ display: 'flex', flexDirection: 'column', gap: 12, padding: 18 }}>
          <BeamInput
            label="Player ID (optional)"
            placeholder="Tick players below, and/or paste a specific ID"
            value={playerId}
            onValueChange={setPlayerId}
          />
          <BeamInput label="Title" placeholder="Notification title" value={title} onValueChange={setTitle} />
          <BeamTextarea label="Body" placeholder="Notification body" rows={3} value={body} onValueChange={setBody} />
          <BeamInput
            label="Deep link (optional)"
            placeholder="e.g. myapp://inbox/42"
            value={deepLink}
            onValueChange={setDeepLink}
          />

          {/* --- Structured campaign editor (§3.3 Notification Intent Data) ----
              All fields below are optional. Leave them blank for an untracked push;
              fill campaignId + nodeId to have the microservice emit a funnel "Sent" event. */}
          <div
            style={{
              borderTop: '1px solid var(--beam-color-neutral-200, #e4e4e7)',
              paddingTop: 12,
              display: 'flex',
              flexDirection: 'column',
              gap: 12,
            }}
          >
            <span style={{ fontWeight: 600 }}>Campaign coordinates (optional)</span>
            <div
              style={{
                display: 'grid',
                gridTemplateColumns: '1fr 1fr',
                gap: 12,
              }}
            >
              <BeamInput label="Campaign ID" placeholder="campaignId" value={campaignId} onValueChange={setCampaignId} />
              <BeamInput label="Node ID" placeholder="nodeId" value={nodeId} onValueChange={setNodeId} />
              <BeamInput label="Account ID" placeholder="accountId" value={accountId} onValueChange={setAccountId} />
              <BeamInput label="cid.pid" placeholder="<cid>.<pid> (defaults to MS realm)" value={cidPid} onValueChange={setCidPid} />
            </div>

            {/* Offers — repeatable {itemId, value, customData} rows */}
            <div style={{ display: 'flex', alignItems: 'center', gap: 12 }}>
              <span style={{ fontWeight: 600 }}>Offers</span>
              <BeamButton appearance="outlined" onClick={addOffer}>
                Add offer
              </BeamButton>
            </div>
            {offers.length === 0 ? (
              <span style={{ fontStyle: 'italic', color: 'var(--beam-color-neutral-500, #71717a)' }}>
                No offers.
              </span>
            ) : (
              offers.map((o, i) => (
                <div
                  key={i}
                  style={{ display: 'grid', gridTemplateColumns: '1fr 1fr 2fr auto', gap: 8, alignItems: 'end' }}
                >
                  <BeamInput
                    label={i === 0 ? 'Item ID' : undefined}
                    placeholder="itemId"
                    value={o.itemId}
                    onValueChange={(v: string) => updateOffer(i, 'itemId', v)}
                  />
                  <BeamInput
                    label={i === 0 ? 'Value' : undefined}
                    placeholder="value"
                    value={o.value}
                    onValueChange={(v: string) => updateOffer(i, 'value', v)}
                  />
                  <div style={{ display: 'flex', flexDirection: 'column', gap: 4 }}>
                    <BeamInput
                      label={i === 0 ? 'Custom data (JSON)' : undefined}
                      placeholder='e.g. {"tier":"gold"}'
                      value={o.customData}
                      onValueChange={(v: string) => updateOffer(i, 'customData', v)}
                      custom-error={invalidCustomDataIdx.has(i) ? 'Invalid JSON' : undefined}
                    />
                    {invalidCustomDataIdx.has(i) && (
                      <span style={{ fontSize: 12, color: 'var(--beam-color-danger-600, #c0392b)' }}>
                        Custom data must be valid JSON (e.g. {'{"tier":"gold"}'}).
                      </span>
                    )}
                  </div>
                  <BeamButton appearance="outlined" onClick={() => removeOffer(i)}>
                    Remove
                  </BeamButton>
                </div>
              ))
            )}

            {/* campaignData — repeatable key→value rows, serialized to a JSON object */}
            <div style={{ display: 'flex', alignItems: 'center', gap: 12 }}>
              <span style={{ fontWeight: 600 }}>Campaign data (key → value)</span>
              <BeamButton appearance="outlined" onClick={addKv}>
                Add field
              </BeamButton>
            </div>
            {campaignData.length === 0 ? (
              <span style={{ fontStyle: 'italic', color: 'var(--beam-color-neutral-500, #71717a)' }}>
                No campaign data fields.
              </span>
            ) : (
              campaignData.map((r, i) => (
                <div key={i} style={{ display: 'grid', gridTemplateColumns: '1fr 2fr auto', gap: 8, alignItems: 'end' }}>
                  <BeamInput
                    label={i === 0 ? 'Key' : undefined}
                    placeholder="key"
                    value={r.key}
                    onValueChange={(v: string) => updateKv(i, 'key', v)}
                  />
                  <BeamInput
                    label={i === 0 ? 'Value' : undefined}
                    placeholder="value"
                    value={r.value}
                    onValueChange={(v: string) => updateKv(i, 'value', v)}
                  />
                  <BeamButton appearance="outlined" onClick={() => removeKv(i)}>
                    Remove
                  </BeamButton>
                </div>
              ))
            )}
          </div>

          <div>
            <BeamButton
              variant="brand"
              onClick={sendPush}
              disabled={!beam || sending || targetCount === 0 || hasInvalidCustomData}
              loading={sending}
            >
              {sending ? 'Sending…' : `Send to ${targetCount} player${targetCount === 1 ? '' : 's'}`}
            </BeamButton>
            {sendError && (
              <span style={{ marginLeft: 12, color: 'var(--beam-color-danger-600, #c0392b)' }}>{sendError}</span>
            )}
          </div>

          {sendResult && (
            <div style={{ marginTop: 4 }}>
              <BeamBadge variant={sendResult.playersOk === sendResult.playersAttempted ? 'success' : 'danger'}>
                {sendResult.playersOk === sendResult.playersAttempted ? 'Sent' : 'Partial'}
              </BeamBadge>
              <span style={{ marginLeft: 10 }}>
                Sent to {sendResult.playersOk}/{sendResult.playersAttempted} player(s) —{' '}
                {sendResult.devicesDelivered} device(s) delivered
                {sendResult.devicesFailed > 0 ? `, ${sendResult.devicesFailed} failed` : ''}
              </span>
              {sendResult.messages.length > 0 && (
                <pre
                  style={{
                    marginTop: 10,
                    padding: 12,
                    background: 'var(--beam-color-neutral-100, #f4f4f5)',
                    borderRadius: 4,
                    overflow: 'auto',
                    whiteSpace: 'pre-wrap',
                  }}
                >
                  {sendResult.messages.join('\n')}
                </pre>
              )}
            </div>
          )}
        </div>
      </BeamCard>

      {/* --- Registered players ---------------------------------------- */}
      <BeamCard>
        <h3 slot="header">
          Registered players{' '}
          {rosterLoading && <BeamSpinner style={{ marginLeft: 8 }} />}
        </h3>
        <div style={{ padding: 18 }}>
          <div style={{ marginBottom: 12, display: 'flex', alignItems: 'center', gap: 12, flexWrap: 'wrap' }}>
            <BeamButton onClick={loadRoster} disabled={!beam || rosterLoading}>
              Refresh
            </BeamButton>
            <BeamButton appearance="outlined" onClick={selectAll} disabled={players.length === 0}>
              Select all
            </BeamButton>
            <BeamButton appearance="outlined" onClick={clearSelection} disabled={selected.size === 0}>
              Clear
            </BeamButton>
            <span style={{ fontWeight: 600 }}>Selected: {selected.size}</span>
            {rosterError && (
              <span style={{ color: 'var(--beam-color-danger-600, #c0392b)' }}>{rosterError}</span>
            )}
            {rosterNote && <span style={{ fontStyle: 'italic' }}>{rosterNote}</span>}
          </div>

          <BeamTable<RegisteredPlayer>
            data={players}
            rowKey={(row) => String(row.playerId)}
            emptyMessage="No players have registered a device yet."
            loading={rosterLoading}
            loadingMessage="Loading roster…"
          >
            <BeamColumn<RegisteredPlayer>
              header=""
              width="44px"
              children={(row) => (
                <BeamCheckbox
                  checked={selected.has(String(row.playerId))}
                  onCheckedChange={() => toggle(String(row.playerId))}
                />
              )}
            />
            <BeamColumn<RegisteredPlayer>
              field="playerId"
              header="Player ID"
              sortable
              format={(value) => String(value)}
            />
            <BeamColumn<RegisteredPlayer> field="deviceCount" header="Devices" sortable align="center" />
            <BeamColumn<RegisteredPlayer>
              header="Push platforms"
              children={(row) => (
                <span style={{ display: 'inline-flex', gap: 6 }}>
                  {row.platforms.map((p) => (
                    <BeamTag key={p}>{p}</BeamTag>
                  ))}
                </span>
              )}
            />
            <BeamColumn<RegisteredPlayer>
              field="gamePlatform"
              header="Game platform"
              sortable
              format={(value) => (value ? String(value) : '—')}
            />
            <BeamColumn<RegisteredPlayer>
              field="gameDevice"
              header="Device"
              sortable
              format={(value) => (value ? String(value) : '—')}
            />
            <BeamColumn<RegisteredPlayer>
              field="lastUpdated"
              header="Last updated"
              sortable
              format={(value) => formatUnixSeconds(value as bigint | string)}
            />
          </BeamTable>
        </div>
      </BeamCard>
    </BeamPage>
  )
}
