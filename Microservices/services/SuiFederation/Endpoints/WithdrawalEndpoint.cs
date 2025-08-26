using System;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Accounts.Exceptions;
using Beamable.SuiFederation.Features.ChannelProcessor;
using Beamable.SuiFederation.Features.Inventory;
using Beamable.SuiFederation.Features.Notifications.Models;
using Beamable.SuiFederation.Features.Transactions;
using Beamable.SuiFederation.Features.Withdrawal;
using Beamable.SuiFederation.Features.Withdrawal.Models;
using SuiFederationCommon;

namespace Beamable.SuiFederation.Endpoints;

public class WithdrawalEndpoint : IEndpoint
{
    private readonly RequestContext _requestContext;
    private readonly WithdrawalService _withdrawalService;
    private readonly TransactionManager _transactionManager;
    private readonly UpdatePlayerStateService _updatePlayerStateService;
    private readonly InventoryService _inventoryService;
    private readonly GetInventoryStateEndpoint _getInventoryStateEndpoint;

    public WithdrawalEndpoint(RequestContext requestContext, WithdrawalService withdrawalService, TransactionManager transactionManager, UpdatePlayerStateService updatePlayerStateService, InventoryService inventoryService, GetInventoryStateEndpoint getInventoryStateEndpoint)
    {
        _requestContext = requestContext;
        _withdrawalService = withdrawalService;
        _transactionManager = transactionManager;
        _updatePlayerStateService = updatePlayerStateService;
        _inventoryService = inventoryService;
        _getInventoryStateEndpoint = getInventoryStateEndpoint;
    }

    public async Task<FederatedInventoryProxyState> Withdraw(string contentId, long amount)
    {
        var microserviceInfo = MicroserviceMetadataExtensions.GetMetadata<SuiFederation, SuiWeb3ExternalIdentity>();
        var existingExternalIdentity = _requestContext.GetExternalIdentity(microserviceInfo);
        if (existingExternalIdentity is null)
            throw new UnknownAccountException("Unknown SuiWeb3ExternalIdentity");

        var request = await _withdrawalService.Initialize(_requestContext.UserId, existingExternalIdentity.userId, contentId, amount);
        var transaction = $"Withdraw-{Guid.NewGuid().ToString()}";
        var withdrawalRequest = new WithdrawalRequest
        {
            GamerTag = _requestContext.UserId,
            ContentId = contentId,
            Amount = amount
        };
        var transactionId = await _transactionManager.StartTransaction(request.PlayerWalletAddress, nameof(Withdraw), transaction, withdrawalRequest);
        _transactionManager.SetCurrentTransactionContext(transactionId);
        _ = _transactionManager.RunAsyncBlock(transactionId, transaction, async () =>
        {
            await ChannelService.Enqueue(_requestContext.UserId, async (_) =>
                await _withdrawalService.Withdraw(transactionId.ToString(), request)
            );

            await ChannelService.Enqueue(_requestContext.UserId, async (_) =>
                await _updatePlayerStateService.Update(new InventoryTransactionNotification
                {
                    InventoryTransactionId = transaction
                }, _getInventoryStateEndpoint, microserviceInfo)
            );
        });
        return await _inventoryService.GetLastKnownState(request.PlayerWalletAddress);
    }
}