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
        let mutable = (request.content.mutableCopy() as? UNMutableNotificationContent)
            ?? UNMutableNotificationContent()
        self.bestAttempt = mutable

        runChain(makePlugins(), content: mutable) { [weak self] final in
            self?.contentHandler?(final)
        }
    }

    /// iOS is about to kill the extension — deliver whatever we have.
    override func serviceExtensionTimeWillExpire() {
        if let handler = contentHandler, let content = bestAttempt {
            handler(content)
        }
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
