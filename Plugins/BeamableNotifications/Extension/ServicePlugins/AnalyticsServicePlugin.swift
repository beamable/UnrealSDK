import UserNotifications
import Foundation
import BeamableNotifications

/// Closed-app analytics (feature 8). Runs in the NSE on remote-push receipt — even when
/// the main app is terminated — and:
///   1. fires a best-effort analytics POST to the endpoint configured via
///      `bmn_configureAnalytics` (shared through the App Group), and
///   2. logs a delivery receipt to the App Group so the app can replay it on next launch.
///
/// The HTTP call is fire-and-forget within the NSE's short execution window; it is not
/// guaranteed to complete, which is why the receipt is also persisted for replay.
public final class AnalyticsServicePlugin: NotificationServicePlugin {

    private let shared: SharedConfig
    private let now: () -> Double

    public init(shared: SharedConfig = .shared, now: @escaping () -> Double = { Date().timeIntervalSince1970 }) {
        self.shared = shared
        self.now = now
    }

    public func process(_ content: UNMutableNotificationContent,
                        completion: @escaping (UNMutableNotificationContent) -> Void) {
        let id = notificationId(from: content.userInfo)

        // Persist a receipt regardless of network outcome (this is the reliable signal).
        var info: [String: JSONValue] = [:]
        if case .object(let obj) = JSONValue(any: content.userInfo) { info = obj }
        shared.appendReceipt(DeliveryReceipt(id: id, timestamp: now(), source: "nse", userInfo: info))

        guard let config = shared.loadAnalyticsConfig(), config.enabled,
              let url = URL(string: config.endpoint) else {
            completion(content)
            return
        }

        // Strip the APNs envelope so `data` mirrors Android's FCM data payload, and pull
        // the deep link tolerant of key spelling (`deeplink` from the backend, etc.).
        var data = info
        data.removeValue(forKey: "aps")

        let payload = AnalyticsPayload.make(
            event: "received",
            source: "nse",
            notificationId: id,
            title: content.title.isEmpty ? nil : content.title,
            body: content.body.isEmpty ? nil : content.body,
            deepLink: info.bmnDeepLink,
            // The NSE only runs for remote pushes delivered while the app is not in the
            // foreground (terminated or background), so this is always false.
            wasForeground: false,
            receivedAtMillis: Int64(now() * 1000),
            data: data,
            config: config
        )

        var request = URLRequest(url: url)
        request.httpMethod = "POST"
        request.setValue("application/json", forHTTPHeaderField: "Content-Type")
        config.headers?.forEach { request.setValue($0.value, forHTTPHeaderField: $0.key) }
        request.httpBody = try? JSON.encoder.encode(payload)

        // Forward content immediately; let the request run in the background.
        URLSession.shared.dataTask(with: request).resume()
        completion(content)
    }

    private func notificationId(from userInfo: [AnyHashable: Any]) -> String {
        if let id = userInfo["bmnId"] as? String { return id }
        if let aps = userInfo["aps"] as? [String: Any], let thread = aps["thread-id"] as? String {
            return thread
        }
        return UUID().uuidString
    }
}
