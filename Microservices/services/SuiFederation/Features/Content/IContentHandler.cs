using System.Collections.Generic;
using System.Threading.Tasks;
using Beamable.Common.Content;
using Beamable.SuiFederation.Features.Content.FunctionMessages;
using Beamable.SuiFederation.Features.Content.Models;
using Beamable.SuiFederation.Features.Inventory.Models;

namespace Beamable.SuiFederation.Features.Content;

public interface IContentHandler
{
    Task<BaseMessage?> ConstructMessage(string transaction, string wallet, InventoryRequest inventoryRequest, IContentObject contentObject);
    Task<BaseMessage?> ConstructMessage(string transaction, string wallet, InventoryRequestUpdate inventoryRequest, IContentObject contentObject);
    Task<BaseMessage?> ConstructMessage(string transaction, string wallet, InventoryRequestDelete inventoryRequest, IContentObject contentObject);
    Task SendMessages(string transaction, List<BaseMessage> messages);
    Task<IFederatedState> GetState(string wallet, string contentId);
}