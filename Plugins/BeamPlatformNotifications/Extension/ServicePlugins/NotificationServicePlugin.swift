import UserNotifications

/// Extension-side counterpart to `NotificationPlugin`. A `NotificationServicePlugin`
/// runs inside the Notification Service Extension process — which executes on remote
/// push receipt even when the main app is killed (as long as the user hasn't force-quit
/// and the push carries `mutable-content:1`). This is where closed-app behavior lives:
/// downloading rich media, firing analytics, logging delivery receipts.
///
/// Add behavior by writing a new conforming type and listing its class name under the
/// `BMNServicePlugins` array in the *extension target's* Info.plist — no edits to the
/// extension host or the SDK core.
public protocol NotificationServicePlugin {
    /// Transform the content (e.g. attach media) and/or perform side effects (analytics).
    /// Always call `completion` exactly once with the content to forward down the chain.
    func process(_ content: UNMutableNotificationContent,
                 completion: @escaping (UNMutableNotificationContent) -> Void)
}
