import UserNotifications
import Foundation

/// The Notification Service Extension host. Each app adds this as an NSE target (the
/// Unity/Unreal post-build steps do it automatically). On every remote push carrying
/// `mutable-content:1` — including when the main app is killed — iOS runs this, giving
/// the SDK a chance to attach media (RichMediaServicePlugin) and track receipt
/// (AnalyticsServicePlugin) even with no engine code alive.
///
/// Plugins run in order. The defaults below ship out of the box; additional service
/// plugins can be added by listing class names under `BMNServicePlugins` in this
/// extension target's Info.plist — no edit to this file.
final class NotificationService: UNNotificationServiceExtension {

    private var contentHandler: ((UNNotificationContent) -> Void)?
    private var bestAttempt: UNMutableNotificationContent?

    /// The plugins for this push, kept so post-chain we can give the funnel-deferring ones a
    /// bounded window to finish their in-flight work before the OS suspends us (FIX 2).
    private var plugins: [NotificationServicePlugin] = []

    /// Once-guard so the OS content handler is invoked EXACTLY once across all paths
    /// (chain+funnel success, budget timeout, or `serviceExtensionTimeWillExpire`).
    private let finishLock = NSLock()
    private var didFinish = false

    /// Total NSE budget we plan against (the OS hard limit is ~30s). We complete comfortably
    /// before this so the system never force-kills us mid-handoff.
    private static let totalBudget: TimeInterval = 27
    /// When the run started, used to compute the funnel wait window left AFTER the chain
    /// (incl. RichMedia download) has already consumed part of the budget.
    private var startTime = Date()

    /// Default chain. Analytics first (so a receipt is logged before any slow media
    /// download), then rich media.
    private func makePlugins() -> [NotificationServicePlugin] {
        var plugins: [NotificationServicePlugin] = [
            AnalyticsServicePlugin(),
            RichMediaServicePlugin()
        ]
        plugins.append(contentsOf: Self.discoverPlugins())
        return plugins
    }

    override func didReceive(_ request: UNNotificationRequest,
                             withContentHandler contentHandler: @escaping (UNNotificationContent) -> Void) {
        self.contentHandler = contentHandler
        self.startTime = Date()
        let mutable = (request.content.mutableCopy() as? UNMutableNotificationContent)
            ?? UNMutableNotificationContent()
        self.bestAttempt = mutable

        let plugins = makePlugins()
        self.plugins = plugins

        // Run the chain (analytics persists its receipt + kicks the funnel POST without
        // blocking; RichMedia downloads media). THEN give the funnel-deferring plugins a
        // bounded window to let the in-flight POST resolve before we hand content to the OS.
        runChain(plugins, content: mutable) { [weak self] final in
            guard let self = self else { return }
            self.bestAttempt = final
            self.awaitDeferredWork { [weak self] in
                self?.finish(with: final)
            }
        }
    }

    /// iOS is about to kill the extension — deliver whatever we have, exactly once.
    override func serviceExtensionTimeWillExpire() {
        finish(with: bestAttempt)
    }

    /// Invoke the OS content handler at most once. Subsequent calls (e.g. a late funnel
    /// completion after `serviceExtensionTimeWillExpire`) are no-ops.
    private func finish(with content: UNMutableNotificationContent?) {
        finishLock.lock()
        if didFinish { finishLock.unlock(); return }
        didFinish = true
        let handler = contentHandler
        finishLock.unlock()

        guard let handler = handler else { return }
        handler(content ?? bestAttempt ?? UNMutableNotificationContent())
    }

    /// After the chain, wait for any `FunnelDeferringPlugin`'s in-flight POST to resolve,
    /// bounded by the remaining budget (so media time already spent is accounted for). Each
    /// deferring plugin persists-for-replay on its own timeout path, so nothing is lost.
    private func awaitDeferredWork(_ done: @escaping () -> Void) {
        let deferring = plugins.compactMap { $0 as? FunnelDeferringPlugin }
        guard !deferring.isEmpty else { done(); return }

        // Budget left after the chain (incl. RichMedia) already ran. Floor at a small positive
        // value so a slow chain still gives the in-flight POST a brief chance to land.
        let elapsed = Date().timeIntervalSince(startTime)
        let remaining = max(Self.totalBudget - elapsed, 0.5)
        let deadline = DispatchTime.now() + remaining

        // Wait for all deferring plugins; call `done` once the last one reports.
        let group = DispatchGroup()
        for plugin in deferring {
            group.enter()
            plugin.awaitPendingFunnel(deadline: deadline) { group.leave() }
        }
        group.notify(queue: .global()) { done() }
    }

    private func runChain(_ plugins: [NotificationServicePlugin],
                          content: UNMutableNotificationContent,
                          done: @escaping (UNMutableNotificationContent) -> Void) {
        var remaining = plugins
        guard !remaining.isEmpty else { done(content); return }
        let next = remaining.removeFirst()
        next.process(content) { [weak self] updated in
            self?.bestAttempt = updated
            self?.runChain(remaining, content: updated, done: done)
        }
    }

    private static func discoverPlugins() -> [NotificationServicePlugin] {
        guard let names = Bundle.main.infoDictionary?["BMNServicePlugins"] as? [String] else { return [] }
        return names.compactMap { name in
            guard let cls = NSClassFromString(name) as? NSObject.Type else { return nil }
            return cls.init() as? NotificationServicePlugin
        }
    }
}
