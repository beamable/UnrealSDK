(function(jsxRuntime, react, client, sdk) {
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
    async sendPushToSelf(params) {
      return this.request({
        endpoint: "SendPushToSelf",
        payload: params,
        withAuth: true
      });
    }
    async sendPushToPlayer(params) {
      return this.request({
        endpoint: "SendPushToPlayer",
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
  function formatUnixSeconds(value) {
    const seconds = Number(value);
    if (!seconds || Number.isNaN(seconds)) return "—";
    return new Date(seconds * 1e3).toLocaleString();
  }
  function App({ context }) {
    const [beam, setBeam] = react.useState(null);
    const [players, setPlayers] = react.useState([]);
    const [rosterLoading, setRosterLoading] = react.useState(false);
    const [rosterError, setRosterError] = react.useState(null);
    const [rosterNote, setRosterNote] = react.useState(null);
    const [playerId, setPlayerId] = react.useState("");
    const [title, setTitle] = react.useState("");
    const [body, setBody] = react.useState("");
    const [deepLink, setDeepLink] = react.useState("");
    const [sending, setSending] = react.useState(false);
    const [sendResult, setSendResult] = react.useState(null);
    const [sendError, setSendError] = react.useState(null);
    react.useEffect(() => {
      let cancelled = false;
      context.beam.then((b2) => {
        if (!cancelled) setBeam(b2);
      });
      return () => {
        cancelled = true;
      };
    }, [context]);
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
    async function sendPush() {
      if (!beam) return;
      if (!playerId.trim()) {
        setSendError("A player ID is required.");
        return;
      }
      if (!title.trim() && !body.trim()) {
        setSendError("A title or body is required.");
        return;
      }
      setSending(true);
      setSendError(null);
      setSendResult(null);
      try {
        const client2 = new BeamFarmMsClient(beam);
        const result = await client2.sendPushToPlayer({
          playerId: playerId.trim(),
          title: title.trim(),
          body: body.trim(),
          deepLink: deepLink.trim()
        });
        setSendResult(result);
        void loadRoster();
      } catch (err) {
        setSendError(err instanceof Error ? err.message : String(err));
      } finally {
        setSending(false);
      }
    }
    return /* @__PURE__ */ jsxRuntime.jsxs(Q, { children: [
      /* @__PURE__ */ jsxRuntime.jsx(ne, { children: "Push Notifications" }),
      /* @__PURE__ */ jsxRuntime.jsxs(b, { style: { marginBottom: 20 }, children: [
        /* @__PURE__ */ jsxRuntime.jsx("h3", { slot: "header", children: "Send a notification" }),
        /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { display: "flex", flexDirection: "column", gap: 12, padding: 18 }, children: [
          /* @__PURE__ */ jsxRuntime.jsx(
            me,
            {
              label: "Player ID",
              placeholder: "Select a player below, or paste an ID",
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
          /* @__PURE__ */ jsxRuntime.jsxs("div", { children: [
            /* @__PURE__ */ jsxRuntime.jsx(
              p,
              {
                variant: "brand",
                onClick: sendPush,
                disabled: !beam || sending,
                loading: sending,
                children: sending ? "Sending…" : "Send push"
              }
            ),
            sendError && /* @__PURE__ */ jsxRuntime.jsx("span", { style: { marginLeft: 12, color: "var(--beam-color-danger-600, #c0392b)" }, children: sendError })
          ] }),
          sendResult && /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { marginTop: 4 }, children: [
            /* @__PURE__ */ jsxRuntime.jsx(g, { variant: sendResult.success ? "success" : "danger", children: sendResult.success ? "Sent" : "Failed" }),
            /* @__PURE__ */ jsxRuntime.jsxs("span", { style: { marginLeft: 10 }, children: [
              sendResult.succeeded,
              "/",
              sendResult.attempted,
              " device(s) delivered",
              sendResult.failed > 0 ? `, ${sendResult.failed} failed` : ""
            ] }),
            sendResult.messages?.length > 0 && /* @__PURE__ */ jsxRuntime.jsx(
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
          /* @__PURE__ */ jsxRuntime.jsxs("div", { style: { marginBottom: 12 }, children: [
            /* @__PURE__ */ jsxRuntime.jsx(p, { onClick: loadRoster, disabled: !beam || rosterLoading, children: "Refresh" }),
            rosterError && /* @__PURE__ */ jsxRuntime.jsx("span", { style: { marginLeft: 12, color: "var(--beam-color-danger-600, #c0392b)" }, children: rosterError }),
            rosterNote && /* @__PURE__ */ jsxRuntime.jsx("span", { style: { marginLeft: 12, fontStyle: "italic" }, children: rosterNote })
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
                    header: "Platforms",
                    children: (row) => /* @__PURE__ */ jsxRuntime.jsx("span", { style: { display: "inline-flex", gap: 6 }, children: row.platforms.map((p2) => /* @__PURE__ */ jsxRuntime.jsx(F, { children: p2 }, p2)) })
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
                ),
                /* @__PURE__ */ jsxRuntime.jsx(
                  Se,
                  {
                    header: "",
                    align: "right",
                    children: (row) => /* @__PURE__ */ jsxRuntime.jsx(p, { size: "small", onClick: () => setPlayerId(String(row.playerId)), children: "Select" })
                  }
                )
              ]
            }
          )
        ] })
      ] })
    ] });
  }
  t.registerExtension({
    beamId: "PushNotifications",
    onMount: (container, context) => {
      const root = client.createRoot(container);
      root.render(
        /* @__PURE__ */ jsxRuntime.jsx(react.StrictMode, { children: /* @__PURE__ */ jsxRuntime.jsx(App, { context }) })
      );
      return root;
    },
    onUnmount: (instance) => {
      instance.unmount();
    }
  });
})(window["@beamable/react-jsx-runtime-19"], window["@beamable/react-19"], window["@beamable/react-dom-client-19"], window["@beamable/sdk-1.2.1"]);
