import { useEffect, useState, useCallback } from 'react'
import { type Beam, type ExtensionContext } from '@beamable/portal-toolkit'
import {
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
} from '@beamable/portal-toolkit/react'
import { BeamFarmMsClient } from '../beamable/clients/BeamFarmMsClient'
import type { RegisteredPlayer, AdminSendResult } from '../beamable/clients/types'

interface AppProps {
  context: ExtensionContext
}

function formatUnixSeconds(value: bigint | string): string {
  const seconds = Number(value)
  if (!seconds || Number.isNaN(seconds)) return '—'
  return new Date(seconds * 1000).toLocaleString()
}

export default function App({ context }: AppProps) {
  const [beam, setBeam] = useState<Beam | null>(null)

  // Roster state
  const [players, setPlayers] = useState<RegisteredPlayer[]>([])
  const [rosterLoading, setRosterLoading] = useState(false)
  const [rosterError, setRosterError] = useState<string | null>(null)
  const [rosterNote, setRosterNote] = useState<string | null>(null)

  // Send form state
  const [playerId, setPlayerId] = useState('')
  const [title, setTitle] = useState('')
  const [body, setBody] = useState('')
  const [deepLink, setDeepLink] = useState('')
  const [sending, setSending] = useState(false)
  const [sendResult, setSendResult] = useState<AdminSendResult | null>(null)
  const [sendError, setSendError] = useState<string | null>(null)

  useEffect(() => {
    let cancelled = false
    context.beam.then((b) => {
      if (!cancelled) setBeam(b)
    })
    return () => {
      cancelled = true
    }
  }, [context])

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

  async function sendPush() {
    if (!beam) return
    if (!playerId.trim()) {
      setSendError('A player ID is required.')
      return
    }
    if (!title.trim() && !body.trim()) {
      setSendError('A title or body is required.')
      return
    }
    setSending(true)
    setSendError(null)
    setSendResult(null)
    try {
      const client = new BeamFarmMsClient(beam)
      const result = await client.sendPushToPlayer({
        playerId: playerId.trim(),
        title: title.trim(),
        body: body.trim(),
        deepLink: deepLink.trim(),
      })
      setSendResult(result)
      // Refresh the roster — a send may have pruned dead tokens.
      void loadRoster()
    } catch (err) {
      setSendError(err instanceof Error ? err.message : String(err))
    } finally {
      setSending(false)
    }
  }

  return (
    <BeamPage>
      <BeamPageHeader>Push Notifications</BeamPageHeader>

      {/* --- Send a push ------------------------------------------------ */}
      <BeamCard style={{ marginBottom: 20 }}>
        <h3 slot="header">Send a notification</h3>
        <div style={{ display: 'flex', flexDirection: 'column', gap: 12, padding: 18 }}>
          <BeamInput
            label="Player ID"
            placeholder="Select a player below, or paste an ID"
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
          <div>
            <BeamButton
              variant="brand"
              onClick={sendPush}
              disabled={!beam || sending}
              loading={sending}
            >
              {sending ? 'Sending…' : 'Send push'}
            </BeamButton>
            {sendError && (
              <span style={{ marginLeft: 12, color: 'var(--beam-color-danger-600, #c0392b)' }}>{sendError}</span>
            )}
          </div>

          {sendResult && (
            <div style={{ marginTop: 4 }}>
              <BeamBadge variant={sendResult.success ? 'success' : 'danger'}>
                {sendResult.success ? 'Sent' : 'Failed'}
              </BeamBadge>
              <span style={{ marginLeft: 10 }}>
                {sendResult.succeeded}/{sendResult.attempted} device(s) delivered
                {sendResult.failed > 0 ? `, ${sendResult.failed} failed` : ''}
              </span>
              {sendResult.messages?.length > 0 && (
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
          <div style={{ marginBottom: 12 }}>
            <BeamButton onClick={loadRoster} disabled={!beam || rosterLoading}>
              Refresh
            </BeamButton>
            {rosterError && (
              <span style={{ marginLeft: 12, color: 'var(--beam-color-danger-600, #c0392b)' }}>{rosterError}</span>
            )}
            {rosterNote && <span style={{ marginLeft: 12, fontStyle: 'italic' }}>{rosterNote}</span>}
          </div>

          <BeamTable<RegisteredPlayer>
            data={players}
            rowKey={(row) => String(row.playerId)}
            emptyMessage="No players have registered a device yet."
            loading={rosterLoading}
            loadingMessage="Loading roster…"
          >
            <BeamColumn<RegisteredPlayer>
              field="playerId"
              header="Player ID"
              sortable
              format={(value) => String(value)}
            />
            <BeamColumn<RegisteredPlayer> field="deviceCount" header="Devices" sortable align="center" />
            <BeamColumn<RegisteredPlayer>
              header="Platforms"
              children={(row) => (
                <span style={{ display: 'inline-flex', gap: 6 }}>
                  {row.platforms.map((p) => (
                    <BeamTag key={p}>{p}</BeamTag>
                  ))}
                </span>
              )}
            />
            <BeamColumn<RegisteredPlayer>
              field="lastUpdated"
              header="Last updated"
              sortable
              format={(value) => formatUnixSeconds(value as bigint | string)}
            />
            <BeamColumn<RegisteredPlayer>
              header=""
              align="right"
              children={(row) => (
                <BeamButton size="small" onClick={() => setPlayerId(String(row.playerId))}>
                  Select
                </BeamButton>
              )}
            />
          </BeamTable>
        </div>
      </BeamCard>
    </BeamPage>
  )
}
