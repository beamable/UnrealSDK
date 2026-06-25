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

/// Opt-in capability for a service plugin that kicks an in-flight network task during
/// `process` but must NOT block the plugin chain on it (so later plugins, e.g. rich-media
/// download, run with the full NSE budget). After the chain completes, `NotificationService`
/// gives every such plugin a bounded window to finish its in-flight work before the OS
/// suspends the extension. See `AnalyticsServicePlugin` and FIX 2.
public protocol FunnelDeferringPlugin {
    /// Wait for any in-flight work to resolve OR until `deadline`, then call `completion`
    /// exactly once. Must return promptly (`completion()` synchronously) when nothing is in
    /// flight. On the deadline path the plugin is responsible for persisting anything that
    /// must survive for replay.
    func awaitPendingFunnel(deadline: DispatchTime, completion: @escaping () -> Void)
}
