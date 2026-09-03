import UserNotifications
import Foundation
import BeamableNotifications

/// Closed-app analytics (§4). Runs in the NSE on remote-push receipt — even when the main
/// app is terminated — and:
///   1. ALWAYS logs a delivery receipt to the App Group (the reliable signal the app
///      replays on next launch), and
///   2. fires a Beamable funnel **Received** event via a best-effort authenticated POST to
///      `/report/custom_batch/...` (§4.3), so a received-but-never-opened notification still
///      reports. If the refresh+POST can't finish within the NSE's ~30s budget, the event is
///      persisted to the App Group for authenticated replay on next app open (§4.3 fallback).
///
/// The funnel event is only emitted for tracked campaigns (`campaignId`+`nodeId`) that also
/// carry the scope/gamerTag needed to authenticate (§4.2). The receipt is logged regardless.
///
/// IMPORTANT (chain altitude): `process` does NOT block the plugin chain on its network POST.
/// It persists the receipt synchronously (the reliable signal), kicks the funnel POST as a
/// tracked background task, and completes IMMEDIATELY so later plugins (RichMedia) get the
/// full NSE budget to download media. The "wait for the in-flight POST before the OS suspends"
/// guarantee is owned by `NotificationService`, which awaits `awaitPendingFunnel` after the
/// whole chain has run. See FIX 2.
public final class AnalyticsServicePlugin: NotificationServicePlugin, FunnelDeferringPlugin {

    private let shared: SharedConfig
    private let session: URLSession
    private let now: () -> Double

    public init(shared: SharedConfig = .shared,
                session: URLSession = .shared,
                now: @escaping () -> Double = { Date().timeIntervalSince1970 }) {
        self.shared = shared
        self.session = session
        self.now = now
    }

    /// Soft deadline handed to `emit` for refresh+POST. The service caps the overall wait with
    /// its own deadline; this is just `emit`'s internal budget for the refresh+POST round-trip.
    private static let emitBudget: TimeInterval = 22

    // In-flight funnel POST tracking. `process` kicks the POST and records its completion;
    // `awaitPendingFunnel` (called by the service after the chain) waits for it, bounded by a
    // deadline. Guarded by `lock` because `emit`'s completion and the service's await race.
    private let lock = NSLock()
    private var funnelInFlight = false
    private var funnelDone = false
    private var funnelWaiter: (() -> Void)?
    /// The event we kicked, kept so the timeout path can persist-for-replay (FIX 2).
    private var pendingEvent: FunnelEvent?

    public func process(_ content: UNMutableNotificationContent,
                        completion: @escaping (UNMutableNotificationContent) -> Void) {
        let id = notificationId(from: content.userInfo)

        // 1) Persist a receipt regardless of network outcome (this is the reliable signal).
        var info: [String: JSONValue] = [:]
        if case .object(let obj) = JSONValue(any: content.userInfo) { info = obj }
        shared.appendReceipt(DeliveryReceipt(id: id, timestamp: now(), source: "nse", userInfo: info))

        // 2) Best-effort funnel "Received" for tracked campaigns. Kicked as a tracked task —
        // it does NOT gate `completion`, so the chain (and RichMedia) proceeds without delay.
        let intent = info.bmnCampaignIntent
        guard let event = BeamableAnalytics.makeEvent(.received, intent: intent) else {
            completion(content)
            return
        }

        lock.lock()
        funnelInFlight = true
        pendingEvent = event
        lock.unlock()

        // persistOnFailure=true routes any event we can't send in time into the replay store
        // (so a failed/late POST isn't lost). When this fires, mark done and wake any waiter.
        BeamableAnalytics.emit(event, shared: shared, session: session,
                               persistOnFailure: true, budget: Self.emitBudget) { [weak self] in
            self?.markFunnelDone()
        }

        // Do not block the chain on the network.
        completion(content)
    }

    private func markFunnelDone() {
        lock.lock()
        guard !funnelDone else { lock.unlock(); return }
        funnelDone = true
        let waiter = funnelWaiter
        funnelWaiter = nil
        lock.unlock()
        waiter?()
    }

    // MARK: FunnelDeferringPlugin

    /// Wait for the in-flight funnel POST to resolve (success or `emit`'s own persist-on-failure)
    /// OR until `deadline`, whichever comes first, then call `completion` exactly once. On the
    /// deadline path the event is persisted for replay so nothing is lost (FIX 2). If no POST was
    /// kicked (no tracked campaign), returns immediately.
    public func awaitPendingFunnel(deadline: DispatchTime, completion: @escaping () -> Void) {
        lock.lock()
        // Nothing in flight, or it already finished — return synchronously.
        if !funnelInFlight || funnelDone {
            lock.unlock()
            completion()
            return
        }

        // Guard so exactly one of {emit-completes, deadline-fires} wins the wakeup.
        var resolved = false
        let resumeOnce: (_ persistOnTimeout: Bool) -> Void = { [weak self] persistOnTimeout in
            guard let self = self else { return }
            self.lock.lock()
            if resolved { self.lock.unlock(); return }
            resolved = true
            self.funnelWaiter = nil
            let event = self.pendingEvent
            self.lock.unlock()
            // On the timeout path `emit` hasn't reported, so persist here so nothing is lost.
            // (The normal path lets `emit`'s own persist-on-failure handle a failed POST.)
            if persistOnTimeout, let event = event { self.shared.appendPendingFunnel(event) }
            completion()
        }

        funnelWaiter = { resumeOnce(false) }
        lock.unlock()

        // Deadline backstop: if `emit` hasn't woken us by `deadline`, finish anyway.
        DispatchQueue.global().asyncAfter(deadline: deadline) { resumeOnce(true) }
    }

    private func notificationId(from userInfo: [AnyHashable: Any]) -> String {
        if let id = userInfo["bmnId"] as? String { return id }
        if let aps = userInfo["aps"] as? [String: Any], let thread = aps["thread-id"] as? String {
            return thread
        }
        return UUID().uuidString
    }
}
