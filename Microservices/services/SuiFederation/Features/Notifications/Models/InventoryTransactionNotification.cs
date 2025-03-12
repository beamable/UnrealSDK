namespace Beamable.SuiFederation.Features.Notifications.Models;

public class InventoryTransactionNotification : IPlayerNotification
{
    public string Context => PlayerNotifications.InventoryTransactionContext;
    public required string InventoryTransactionId { get; init; }
}