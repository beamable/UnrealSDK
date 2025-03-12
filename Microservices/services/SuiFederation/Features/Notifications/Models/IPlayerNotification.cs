namespace Beamable.SuiFederation.Features.Notifications.Models;

public interface IPlayerNotification
{
    string Context { get; }
    string InventoryTransactionId { get; }
}