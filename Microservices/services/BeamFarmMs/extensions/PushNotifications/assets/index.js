(function(react, client, jsxRuntime, sdk) {
  "use strict";
  function e(e2) {
    let t2 = { mount: (t3, n) => e2.onMount(t3, n), unmount: (t3) => e2.onUnmount(t3), ...e2.getBadge ? { getBadge: e2.getBadge } : {} };
    window[e2.beamId] = t2;
  }
  const t = { registerExtension: e };
  function l(e2) {
    let t2 = ((typeof globalThis < `u` ? globalThis.__beamPortal?.react : void 0) ?? {})[e2];
    if (!t2) throw Error(`Beam React component "${e2}" is not provided by the host portal. Extensions must run inside the Beamable portal — see https://help.beamable.com/ for the extension setup guide.`);
    return t2;
  }
  function d(e2) {
    return react.createElement(l(`BeamSpinner`), e2);
  }
  d.displayName = `BeamSpinner`;
  function p(e2) {
    return react.createElement(l(`BeamButton`), e2);
  }
  p.displayName = `BeamButton`;
  function g(e2) {
    return react.createElement(l(`BeamBadge`), e2);
  }
  g.displayName = `BeamBadge`;
  function b(e2) {
    return react.createElement(l(`BeamCard`), e2);
  }
  b.displayName = `BeamCard`;
  function F(e2) {
    return react.createElement(l(`BeamTag`), e2);
  }
  F.displayName = `BeamTag`;
  function Q(e2) {
    return react.createElement(l(`BeamPage`), e2);
  }
  Q.displayName = `BeamPage`;
  function ne(e2) {
    return react.createElement(l(`BeamPageHeader`), e2);
  }
  ne.displayName = `BeamPageHeader`;
  function pe(e2) {
    return react.createElement(l(`BeamCheckbox`), e2);
  }
  pe.displayName = `BeamCheckbox`;
  function me(e2) {
    return react.createElement(l(`BeamInput`), e2);
  }
  me.displayName = `BeamInput`;
  function xe(e2) {
    return react.createElement(l(`BeamTextarea`), e2);
  }
  xe.displayName = `BeamTextarea`;
  function Se(e2) {
    return null;
  }
  Se.displayName = `BeamColumn`;
  function Te(e2) {
    return react.createElement(l(`BeamTable`), e2);
  }
  Te.displayName = `BeamTable`;
  function ke(e2) {
    let [t2, n] = react.useState(null);
    return react.useEffect(() => {
      let t3 = false;
      return e2.beam.then((e3) => {
        t3 || n(e3);
      }), () => {
        t3 = true;
      };
    }, [e2.beam]), t2;
  }
  function Ae(r) {
    let { beamId: i, App: a, disableStrictMode: o, wrapper: s, getBadge: l2 } = r;
    t.registerExtension({ beamId: i, onMount: (e2, r2) => {
      let i2 = client.createRoot(e2), l3 = react.createElement(a, { context: r2 }), u = s ? s({ context: r2, children: l3 }) : l3;
      return i2.render(o ? u : react.createElement(react.StrictMode, null, u)), i2;
    }, onUnmount: (e2) => {
      e2.unmount();
    }, ...l2 ? { getBadge: l2 } : {} });
  }
  const name = "PushNotifications";
  class BeamFarmMsClient extends sdk.BeamMicroServiceClient {
    federationIds = {
      google: "google",
      gamecenter: "gamecenter"
    };
    constructor(beam) {
      super(beam);
    }
    get serviceName() {
      return "BeamFarmMs";
    }
    async plantSeed(params) {
      return this.request({
        endpoint: "PlantSeed",
        payload: params,
        withAuth: true
      });
    }
    async collectHarvest(params) {
      return this.request({
        endpoint: "CollectHarvest",
        payload: params,
        withAuth: true
      });
    }
    async getSlotStates(params) {
      return this.request({
        endpoint: "GetSlotStates",
        payload: params,
        withAuth: true
      });
    }
    async registerGroundItem(params) {
      return this.request({
        endpoint: "RegisterGroundItem",
        payload: params,
        withAuth: true
      });
    }
    async collectGroundItem(params) {
      return this.request({
        endpoint: "CollectGroundItem",
        payload: params,
        withAuth: true
      });
    }
    async getGroundItems(params) {
      return this.request({
        endpoint: "GetGroundItems",
        payload: params,
        withAuth: true
      });
    }
    async getDeliveryOrders() {
      return this.request({
        endpoint: "GetDeliveryOrders",
        withAuth: true
      });
    }
    async fillDeliveryOrders() {
      return this.request({
        endpoint: "FillDeliveryOrders",
        withAuth: true
      });
    }
    async deliverOrder(params) {
      return this.request({
        endpoint: "DeliverOrder",
        payload: params,
        withAuth: true
      });
    }
    async mutateWithModifiers(params) {
      return this.request({
        endpoint: "MutateWithModifiers",
        payload: params,
        withAuth: true
      });
    }
    async startResearch(params) {
      return this.request({
        endpoint: "StartResearch",
        payload: params,
        withAuth: true
      });
    }
    async collectResearch(params) {
      return this.request({
        endpoint: "CollectResearch",
        payload: params,
        withAuth: true
      });
    }
    async getPlayerLevel() {
      return this.request({
        endpoint: "GetPlayerLevel",
        withAuth: true
      });
    }
    async registerDeviceToken(params) {
      return this.request({
        endpoint: "RegisterDeviceToken",
        payload: params,
        withAuth: true
      });
    }
    async unregisterDeviceToken(params) {
      return this.request({
        endpoint: "UnregisterDeviceToken",
        payload: params,
        withAuth: true
      });
    }
    async listMyDevices() {
      return this.request({
        endpoint: "ListMyDevices",
        withAuth: true
      });
    }
    async sendCampaignPushToSelf(params) {
      return this.request({
        endpoint: "SendCampaignPushToSelf",
        payload: params,
        withAuth: true
      });
    }
    async sendCampaignPushToPlayer(params) {
      return this.request({
        endpoint: "SendCampaignPushToPlayer",
        payload: params,
        withAuth: true
      });
    }
    async listRegisteredPlayers() {
      return this.request({
        endpoint: "ListRegisteredPlayers",
        withAuth: true
      });
    }
    async checkFcmConfig() {
      return this.request({
        endpoint: "CheckFcmConfig",
        withAuth: true
      });
    }
  }
  function kvRowsToJson(rows) {
    const obj = {};
    let any = false;
    for (const r of rows) {
      const k = r.key.trim();
      if (!k) continue;
      obj[k] = r.value;
      any = true;
    }
    return any ? JSON.stringify(obj) : "";
  }
  function formatUnixSeconds(value) {
    const seconds = Number(value);
    if (!seconds || Number.isNaN(seconds)) return "—";
    return new Date(seconds * 1e3).toLocaleString();
  }
  function App({ context }) {
    const beam = ke(context);
    const [players, setPlayers] = react.useState([]);
    const [rosterLoading, setRosterLoading] = react.useState(false);
    const [rosterError, setRosterError] = react.useState(null);
    const [rosterNote, setRosterNote] = react.useState(null);
    const [selected, setSelected] = react.useState(/* @__PURE__ */ new Set());
    const [playerId, setPlayerId] = react.useState("");
    const [title, setTitle] = react.useState("");
    const [body, setBody] = react.useState("");
    const [deepLink, setDeepLink] = react.useState("");
    const [sending, setSending] = react.useState(false);
    const [sendResult, setSendResult] = react.useState(null);
    const [sendError, setSendError] = react.useState(null);
    const [campaignId, setCampaignId] = react.useState("");
    const [nodeId, setNodeId] = react.useState("");
    const [accountId, setAccountId] = react.useState("");
    const [cidPid, setCidPid] = react.useState("");
    const [offers, setOffers] = react.useState([]);
    const [campaignData, setCampaignData] = react.useState([]);
    const loadRoster = react.useCallback(async () => {
      if (!beam) return;
      setRosterLoading(true);
      setRosterError(null);
      setRosterNote(null);
      try {
        const client2 = new BeamFarmMsClient(beam);
        const result = await client2.listRegisteredPlayers();
        setPlayers(result.players ?? []);
        setRosterNote(result.message ?? null);
      } catch (err) {
        setRosterError(err instanceof Error ? err.message : String(err));
      } finally {
        setRosterLoading(false);
      }
    }, [beam]);
    react.useEffect(() => {
      if (beam) void loadRoster();
    }, [beam, loadRoster]);
    const toggle = react.useCallback((id) => {
      setSelected((prev) => {
        const next = new Set(prev);
        if (next.has(id)) next.delete(id);
        else next.add(id);
        return next;
      });
    }, []);
    const selectAll = react.useCallback(() => {
      setSelected(new Set(players.map((p2) => String(p2.playerId))));
    }, [players]);
    const clearSelection = react.useCallback(() => setSelected(/* @__PURE__ */ new Set()), []);
    const addOffer = react.useCallback(
      () => setOffers((prev) => [...prev, { itemId: "", value: "", customData: "" }]),
      []
    );
    const removeOffer = react.useCallback(
      (i) => setOffers((prev) => prev.filter((_, idx) => idx !== i)),
      []
    );
    const updateOffer = react.useCallback(
      (i, field, value) => setOffers((prev) => prev.map((o, idx) => idx === i ? { ...o, [field]: value } : o)),
      []
    );
    const addKv = react.useCallback(
      () => setCampaignData((prev) => [...prev, { key: "", value: "" }]),
      []
    );
    const removeKv = react.useCallback(
      (i) => setCampaignData((prev) => prev.filter((_, idx) => idx !== i)),
      []
    );
    const updateKv = react.useCallback(
      (i, field, value) => setCampaignData((prev) => prev.map((r, idx) => idx === i ? { ...r, [field]: value } : r)),
      []
    );
    const targets = react.useMemo(() => {
      const t2 = new Set(selected);
      if (playerId.trim()) t2.add(playerId.trim());
      return t2;
    }, [selected, playerId]);
    const invalidCustomDataIdx = react.useMemo(() => {
      const bad = /* @__PURE__ */ new Set();
      offers.forEach((o, i) => {
        const custom = o.customData.trim();
        if (!custom) return;
        try {
          JSON.parse(custom);
        } catch {
          bad.add(i);
        }
      });
      return bad;
    }, [offers]);
    const hasInvalidCustomData = invalidCustomDataIdx.size > 0;
    async function sendPush() {
      if (!beam) return;
      if (targets.size === 0) {
        setSendError("Select at least one player (or type a player ID).");
        return;
      }
      if (!title.trim() && !body.trim()) {
        setSendError("A title or body is required.");
        return;
      }
      if (hasInvalidCustomData) {
        setSendError("One or more offers have invalid JSON in Custom data.");
        return;
      }
      setSending(true);
      setSendError(null);
      setSendResult(null);
      const client2 = new BeamFarmMsClient(beam);
      const builtOffers = offers.filter((o) => o.itemId.trim() || o.value.trim() || o.customData.trim()).map((o) => ({
        itemId: o.itemId.trim(),
        value: o.value.trim(),
        customData: o.customData.trim()
      }));
      const campaignDataJson = kvRowsToJson(campaignData);
      const campaignRequest = {
        title: title.trim(),
        body: body.trim(),
        deepLink: deepLink.trim(),
        campaignId: campaignId.trim(),
        nodeId: nodeId.trim(),
        gamerTag: "",
        // defaults to the target player id server-side
        accountId: accountId.trim(),
        cidPid: cidPid.trim(),
        offers: builtOffers,
        campaignData: campaignDataJson
      };
      const outcomes = await Promise.all(
        [...targets].map(
          (id) => client2.sendCampaignPushToPlayer({ playerId: id, request: campaignRequest }).then((r) => ({ id, r })).catch((e2) => ({ id, err: e2 instanceof Error ? e2.message : String(e2) }))
        )
      );
      const agg = {
        playersAttempted: targets.size,
        playersOk: 0,
        devicesDelivered: 0,
        devicesFailed: 0,
        messages: []
      };
      for (const o of outcomes) {
        if ("err" in o) {
          agg.messages.push(`${o.id}: ${o.err}`);
          continue;
        }
        const r = o.r;
        if (r.success) agg.playersOk++;
        agg.devicesDelivered += r.succeeded;
        agg.devicesFailed += r.failed;
        for (const m of r.messages ?? []) agg.messages.push(`${o.id}: ${m}`);
      }
      setSendResult(agg);
      setSending(false);
      void loadRoster();
    }
    const targetCount = targets.size;
    return /* @__PURE__ */ jsxRuntime.jsxs(Q, { children: [
      /* @__PURE__ */ jsxRuntime.jsx(ne, { children: "Push Notifications" }),
      /* @__PURE__ */ jsxRuntime.jsxs(b, { style: { marginBottom: 20 }, children: [
        /* @__PURE__ */ jsxRuntime.jsx("h3", { slot: "header", children: "Send a notification" }),
        /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { display: "flex", flexDirection: "column", gap: 12, padding: 18 }, children: [
          /* @__PURE__ */ jsxRuntime.jsx(
            me,
            {
              label: "Player ID (optional)",
              placeholder: "Tick players below, and/or paste a specific ID",
              value: playerId,
              onValueChange: setPlayerId
            }
          ),
          /* @__PURE__ */ jsxRuntime.jsx(me, { label: "Title", placeholder: "Notification title", value: title, onValueChange: setTitle }),
          /* @__PURE__ */ jsxRuntime.jsx(xe, { label: "Body", placeholder: "Notification body", rows: 3, value: body, onValueChange: setBody }),
          /* @__PURE__ */ jsxRuntime.jsx(
            me,
            {
              label: "Deep link (optional)",
              placeholder: "e.g. myapp://inbox/42",
              value: deepLink,
              onValueChange: setDeepLink
            }
          ),
          /* @__PURE__ */ jsxRuntime.jsxs(
            "div",
            {
              style: {
                borderTop: "1px solid var(--beam-color-neutral-200, #e4e4e7)",
                paddingTop: 12,
                display: "flex",
                flexDirection: "column",
                gap: 12
              },
              children: [
                /* @__PURE__ */ jsxRuntime.jsx("span", { style: { fontWeight: 600 }, children: "Campaign coordinates (optional)" }),
                /* @__PURE__ */ jsxRuntime.jsxs(
                  "div",
                  {
                    style: {
                      display: "grid",
                      gridTemplateColumns: "1fr 1fr",
                      gap: 12
                    },
                    children: [
                      /* @__PURE__ */ jsxRuntime.jsx(me, { label: "Campaign ID", placeholder: "campaignId", value: campaignId, onValueChange: setCampaignId }),
                      /* @__PURE__ */ jsxRuntime.jsx(me, { label: "Node ID", placeholder: "nodeId", value: nodeId, onValueChange: setNodeId }),
                      /* @__PURE__ */ jsxRuntime.jsx(me, { label: "Account ID", placeholder: "accountId", value: accountId, onValueChange: setAccountId }),
                      /* @__PURE__ */ jsxRuntime.jsx(me, { label: "cid.pid", placeholder: "<cid>.<pid> (defaults to MS realm)", value: cidPid, onValueChange: setCidPid })
                    ]
                  }
                ),
                /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { display: "flex", alignItems: "center", gap: 12 }, children: [
                  /* @__PURE__ */ jsxRuntime.jsx("span", { style: { fontWeight: 600 }, children: "Offers" }),
                  /* @__PURE__ */ jsxRuntime.jsx(p, { appearance: "outlined", onClick: addOffer, children: "Add offer" })
                ] }),
                offers.length === 0 ? /* @__PURE__ */ jsxRuntime.jsx("span", { style: { fontStyle: "italic", color: "var(--beam-color-neutral-500, #71717a)" }, children: "No offers." }) : offers.map((o, i) => /* @__PURE__ */ jsxRuntime.jsxs(
                  "div",
                  {
                    style: { display: "grid", gridTemplateColumns: "1fr 1fr 2fr auto", gap: 8, alignItems: "end" },
                    children: [
                      /* @__PURE__ */ jsxRuntime.jsx(
                        me,
                        {
                          label: i === 0 ? "Item ID" : void 0,
                          placeholder: "itemId",
                          value: o.itemId,
                          onValueChange: (v) => updateOffer(i, "itemId", v)
                        }
                      ),
                      /* @__PURE__ */ jsxRuntime.jsx(
                        me,
                        {
                          label: i === 0 ? "Value" : void 0,
                          placeholder: "value",
                          value: o.value,
                          onValueChange: (v) => updateOffer(i, "value", v)
                        }
                      ),
                      /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { display: "flex", flexDirection: "column", gap: 4 }, children: [
                        /* @__PURE__ */ jsxRuntime.jsx(
                          me,
                          {
                            label: i === 0 ? "Custom data (JSON)" : void 0,
                            placeholder: 'e.g. {"tier":"gold"}',
                            value: o.customData,
                            onValueChange: (v) => updateOffer(i, "customData", v),
                            "custom-error": invalidCustomDataIdx.has(i) ? "Invalid JSON" : void 0
                          }
                        ),
                        invalidCustomDataIdx.has(i) && /* @__PURE__ */ jsxRuntime.jsxs("span", { style: { fontSize: 12, color: "var(--beam-color-danger-600, #c0392b)" }, children: [
                          "Custom data must be valid JSON (e.g. ",
                          '{"tier":"gold"}',
                          ")."
                        ] })
                      ] }),
                      /* @__PURE__ */ jsxRuntime.jsx(p, { appearance: "outlined", onClick: () => removeOffer(i), children: "Remove" })
                    ]
                  },
                  i
                )),
                /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { display: "flex", alignItems: "center", gap: 12 }, children: [
                  /* @__PURE__ */ jsxRuntime.jsx("span", { style: { fontWeight: 600 }, children: "Campaign data (key → value)" }),
                  /* @__PURE__ */ jsxRuntime.jsx(p, { appearance: "outlined", onClick: addKv, children: "Add field" })
                ] }),
                campaignData.length === 0 ? /* @__PURE__ */ jsxRuntime.jsx("span", { style: { fontStyle: "italic", color: "var(--beam-color-neutral-500, #71717a)" }, children: "No campaign data fields." }) : campaignData.map((r, i) => /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { display: "grid", gridTemplateColumns: "1fr 2fr auto", gap: 8, alignItems: "end" }, children: [
                  /* @__PURE__ */ jsxRuntime.jsx(
                    me,
                    {
                      label: i === 0 ? "Key" : void 0,
                      placeholder: "key",
                      value: r.key,
                      onValueChange: (v) => updateKv(i, "key", v)
                    }
                  ),
                  /* @__PURE__ */ jsxRuntime.jsx(
                    me,
                    {
                      label: i === 0 ? "Value" : void 0,
                      placeholder: "value",
                      value: r.value,
                      onValueChange: (v) => updateKv(i, "value", v)
                    }
                  ),
                  /* @__PURE__ */ jsxRuntime.jsx(p, { appearance: "outlined", onClick: () => removeKv(i), children: "Remove" })
                ] }, i))
              ]
            }
          ),
          /* @__PURE__ */ jsxRuntime.jsxs("div", { children: [
            /* @__PURE__ */ jsxRuntime.jsx(
              p,
              {
                variant: "brand",
                onClick: sendPush,
                disabled: !beam || sending || targetCount === 0 || hasInvalidCustomData,
                loading: sending,
                children: sending ? "Sending…" : `Send to ${targetCount} player${targetCount === 1 ? "" : "s"}`
              }
            ),
            sendError && /* @__PURE__ */ jsxRuntime.jsx("span", { style: { marginLeft: 12, color: "var(--beam-color-danger-600, #c0392b)" }, children: sendError })
          ] }),
          sendResult && /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { marginTop: 4 }, children: [
            /* @__PURE__ */ jsxRuntime.jsx(g, { variant: sendResult.playersOk === sendResult.playersAttempted ? "success" : "danger", children: sendResult.playersOk === sendResult.playersAttempted ? "Sent" : "Partial" }),
            /* @__PURE__ */ jsxRuntime.jsxs("span", { style: { marginLeft: 10 }, children: [
              "Sent to ",
              sendResult.playersOk,
              "/",
              sendResult.playersAttempted,
              " player(s) —",
              " ",
              sendResult.devicesDelivered,
              " device(s) delivered",
              sendResult.devicesFailed > 0 ? `, ${sendResult.devicesFailed} failed` : ""
            ] }),
            sendResult.messages.length > 0 && /* @__PURE__ */ jsxRuntime.jsx(
              "pre",
              {
                style: {
                  marginTop: 10,
                  padding: 12,
                  background: "var(--beam-color-neutral-100, #f4f4f5)",
                  borderRadius: 4,
                  overflow: "auto",
                  whiteSpace: "pre-wrap"
                },
                children: sendResult.messages.join("\n")
              }
            )
          ] })
        ] })
      ] }),
      /* @__PURE__ */ jsxRuntime.jsxs(b, { children: [
        /* @__PURE__ */ jsxRuntime.jsxs("h3", { slot: "header", children: [
          "Registered players",
          " ",
          rosterLoading && /* @__PURE__ */ jsxRuntime.jsx(d, { style: { marginLeft: 8 } })
        ] }),
        /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { padding: 18 }, children: [
          /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { marginBottom: 12, display: "flex", alignItems: "center", gap: 12, flexWrap: "wrap" }, children: [
            /* @__PURE__ */ jsxRuntime.jsx(p, { onClick: loadRoster, disabled: !beam || rosterLoading, children: "Refresh" }),
            /* @__PURE__ */ jsxRuntime.jsx(p, { appearance: "outlined", onClick: selectAll, disabled: players.length === 0, children: "Select all" }),
            /* @__PURE__ */ jsxRuntime.jsx(p, { appearance: "outlined", onClick: clearSelection, disabled: selected.size === 0, children: "Clear" }),
            /* @__PURE__ */ jsxRuntime.jsxs("span", { style: { fontWeight: 600 }, children: [
              "Selected: ",
              selected.size
            ] }),
            rosterError && /* @__PURE__ */ jsxRuntime.jsx("span", { style: { color: "var(--beam-color-danger-600, #c0392b)" }, children: rosterError }),
            rosterNote && /* @__PURE__ */ jsxRuntime.jsx("span", { style: { fontStyle: "italic" }, children: rosterNote })
          ] }),
          /* @__PURE__ */ jsxRuntime.jsxs(
            Te,
            {
              data: players,
              rowKey: (row) => String(row.playerId),
              emptyMessage: "No players have registered a device yet.",
              loading: rosterLoading,
              loadingMessage: "Loading roster…",
              children: [
                /* @__PURE__ */ jsxRuntime.jsx(
                  Se,
                  {
                    header: "",
                    width: "44px",
                    children: (row) => /* @__PURE__ */ jsxRuntime.jsx(
                      pe,
                      {
                        checked: selected.has(String(row.playerId)),
                        onCheckedChange: () => toggle(String(row.playerId))
                      }
                    )
                  }
                ),
                /* @__PURE__ */ jsxRuntime.jsx(
                  Se,
                  {
                    field: "playerId",
                    header: "Player ID",
                    sortable: true,
                    format: (value) => String(value)
                  }
                ),
                /* @__PURE__ */ jsxRuntime.jsx(Se, { field: "deviceCount", header: "Devices", sortable: true, align: "center" }),
                /* @__PURE__ */ jsxRuntime.jsx(
                  Se,
                  {
                    header: "Push platforms",
                    children: (row) => /* @__PURE__ */ jsxRuntime.jsx("span", { style: { display: "inline-flex", gap: 6 }, children: row.platforms.map((p2) => /* @__PURE__ */ jsxRuntime.jsx(F, { children: p2 }, p2)) })
                  }
                ),
                /* @__PURE__ */ jsxRuntime.jsx(
                  Se,
                  {
                    field: "gamePlatform",
                    header: "Game platform",
                    sortable: true,
                    format: (value) => value ? String(value) : "—"
                  }
                ),
                /* @__PURE__ */ jsxRuntime.jsx(
                  Se,
                  {
                    field: "gameDevice",
                    header: "Device",
                    sortable: true,
                    format: (value) => value ? String(value) : "—"
                  }
                ),
                /* @__PURE__ */ jsxRuntime.jsx(
                  Se,
                  {
                    field: "lastUpdated",
                    header: "Last updated",
                    sortable: true,
                    format: (value) => formatUnixSeconds(value)
                  }
                )
              ]
            }
          )
        ] })
      ] })
    ] });
  }
  Ae({ beamId: name, App });
})(window["@beamable/react-19"], window["@beamable/react-dom-client-19"], window["@beamable/react-jsx-runtime-19"], window["@beamable/sdk-1.2.1"]);
