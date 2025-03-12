using System;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace Beamable.SuiFederation.Features.Notifications.Models;

public class NotificationConverter : JsonConverter<IPlayerNotification>
{
    public override IPlayerNotification? Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
    {
        using var jsonDoc = JsonDocument.ParseValue(ref reader);
        var root = jsonDoc.RootElement;
        var context = root.GetProperty("Context").GetString();

        return context switch
        {
            PlayerNotifications.InventoryTransactionContext => JsonSerializer.Deserialize<InventoryTransactionNotification>(root.GetRawText(), options),
            _ => throw new NotSupportedException($"Context '{context}' is not supported.")
        };
    }

    public override void Write(Utf8JsonWriter writer, IPlayerNotification value, JsonSerializerOptions options)
    {
        JsonSerializer.Serialize(writer, value, value.GetType(), options);
    }
}

public static class PlayerNotifications
{
    public const string InventoryTransactionContext = "inventory-transaction";
}