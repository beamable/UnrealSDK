package com.beamable.unreal;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;

import com.beamable.push.PushNotificationReceivedHandler;
import com.beamable.push.PushReceivedEvent;

import org.json.JSONObject;

import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.nio.charset.StandardCharsets;

/**
 * Closed-app delivery analytics for the Unreal integration — the Android counterpart of the iOS
 * Notification Service Extension. It fires on push receipt even when the app is fully killed, where
 * no Unreal runtime exists, so it must be self-contained native code (see
 * {@link PushNotificationReceivedHandler}).
 *
 * Registered via AndroidManifest meta-data (injected by BeamPlatformNotifications_APL.xml):
 *   <meta-data android:name="com.beamable.push.notification_received_handler"
 *              android:value="com.beamable.unreal.BeamUnrealPushReceivedHandler"/>
 * which requires the public no-arg constructor below (the core instantiates it by reflection).
 *
 * Unlike the React Native sample's handler — which bakes the webhook URL in as a constant — the
 * endpoint here is read at receive time from the manifest meta-data
 * `com.beamable.analytics.endpoint` (also injected by the APL from
 * `[BeamPlatformNotifications] AnalyticsEndpoint` in DefaultEngine.ini). This mirrors how the iOS
 * NSE reads its endpoint from Info.plist, so all three reporting paths share one config value.
 *
 * Fires for LOCAL notifications (via NotificationActionReceiver) and for REMOTE **data-only**,
 * high-priority FCM messages. A `notification`-block FCM message is shown by the OS and only
 * reaches the app on tap, so use data-only messages to exercise the killed-app path.
 *
 * Threading: runs on FCM's background thread with a ~10s budget, so a short blocking POST is fine.
 */
public class BeamUnrealPushReceivedHandler implements PushNotificationReceivedHandler {

    private static final String TAG = "BeamUnrealHook";
    private static final String ENDPOINT_META = "com.beamable.analytics.endpoint";

    public BeamUnrealPushReceivedHandler() {
    }

    @Override
    public void onNotificationReceived(Context context, PushReceivedEvent event) {
        try {
            String endpoint = readEndpoint(context);
            if (TextUtils.isEmpty(endpoint)) {
                // No analytics endpoint configured — nothing to report.
                return;
            }
            postWebhook(endpoint, "📬 " + titleOf(event) + " delivered (app closed)");
        } catch (Throwable t) {
            Log.w(TAG, "Failed to post delivery webhook: " + t.getMessage());
        }
    }

    /** Reads the analytics endpoint baked into the manifest by the APL. */
    private static String readEndpoint(Context context) {
        try {
            ApplicationInfo ai = context.getPackageManager().getApplicationInfo(
                context.getPackageName(), PackageManager.GET_META_DATA);
            Bundle meta = ai.metaData;
            return meta != null ? meta.getString(ENDPOINT_META) : null;
        } catch (Throwable t) {
            return null;
        }
    }

    /** Best-effort title for the message: the data payload's "title", else the FCM message id. */
    private static String titleOf(PushReceivedEvent e) {
        try {
            JSONObject data = new JSONObject(e.getDataJson());
            String title = data.optString("title", null);
            if (!TextUtils.isEmpty(title)) {
                return title;
            }
        } catch (Throwable ignored) {
            // dataJson may be empty or non-object — fall through.
        }
        String id = e.getMessageId();
        return TextUtils.isEmpty(id) ? "(untitled)" : id;
    }

    private static void postWebhook(String endpoint, String message) throws Exception {
        HttpURLConnection conn = (HttpURLConnection) new URL(endpoint).openConnection();
        try {
            conn.setRequestMethod("POST");
            conn.setConnectTimeout(8000);
            conn.setReadTimeout(8000);
            conn.setDoOutput(true);
            conn.setRequestProperty("Content-Type", "application/json; charset=utf-8");

            byte[] body = ("{\"message\":\"" + jsonEscape(message) + "\"}")
                .getBytes(StandardCharsets.UTF_8);
            try (OutputStream os = conn.getOutputStream()) {
                os.write(body);
            }

            int code = conn.getResponseCode();
            Log.i(TAG, "Delivery webhook response: " + code);
        } finally {
            conn.disconnect();
        }
    }

    private static String jsonEscape(String s) {
        if (s == null) {
            return "";
        }
        StringBuilder b = new StringBuilder(s.length() + 16);
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            switch (c) {
                case '"':  b.append("\\\""); break;
                case '\\': b.append("\\\\"); break;
                case '\n': b.append("\\n");  break;
                case '\r': b.append("\\r");  break;
                case '\t': b.append("\\t");  break;
                default:
                    if (c < 0x20) {
                        b.append(String.format("\\u%04x", (int) c));
                    } else {
                        b.append(c);
                    }
            }
        }
        return b.toString();
    }
}
