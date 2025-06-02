using System;
using System.Collections.Generic;
using System.Text.Json;
using System.Threading;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Common.Api.Inventory;
using Beamable.Server;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Transactions.Exceptions;
using Beamable.SuiFederation.Features.Transactions.Storage;
using Beamable.SuiFederation.Features.Transactions.Storage.Models;
using Beamable.SuiFederation.Features.Withdrawal.Models;
using MongoDB.Bson;
using Serilog;

namespace Beamable.SuiFederation.Features.Transactions;

public class TransactionManager
{
    private readonly InventoryTransactionCollection _inventoryTransactionCollection;
    private readonly TransactionLogCollection _transactionLogCollection;
    private readonly RequestContext _requestContext;

    private readonly AsyncLocal<ObjectId?> _currentTransaction = new();
    private static int _inflightTransactions;

    private static readonly JsonSerializerOptions JsonSerializerOptions = new()
    {
        IncludeFields = true
    };

    public TransactionManager(InventoryTransactionCollection inventoryTransactionCollection, TransactionLogCollection transactionLogCollection, RequestContext requestContext)
    {
        _inventoryTransactionCollection = inventoryTransactionCollection;
        _transactionLogCollection = transactionLogCollection;
        _requestContext = requestContext;
    }

    public static void SetupShutdownHook()
    {
        Log.Debug("Registering transaction shutdown hook");
        AppDomain.CurrentDomain.ProcessExit += (_, _) =>
        {
            Log.Debug("Waiting for inflight transactions");
            var inflightTransactions = _inflightTransactions;

            while (inflightTransactions > 0)
            {
                Log.Debug("{InflightTransactions} inflight transactions, waiting for 500ms", inflightTransactions);
                Thread.Sleep(500);
                inflightTransactions = _inflightTransactions;
            }
            Log.Debug("Done waiting for inflight transactions");
        };
    }

    public void SetCurrentTransactionContext(ObjectId transactionId)
    {
        _currentTransaction.Value = transactionId;
    }

    public void SetCurrentTransactionContext(string transactionId)
    {
        _currentTransaction.Value = ObjectId.Parse(transactionId);
    }

    public async Task<ObjectId> StartTransaction(string walletAddress, string operationName, string inventoryTransaction, WithdrawalRequest requestedTransfer)
    {
        return await StartTransaction(walletAddress, inventoryTransaction, operationName, new
        {
            requestedTransfer
        });
    }

    public async Task<ObjectId> StartTransaction(string walletAddress, string operationName, string inventoryTransaction, Dictionary<string, long> currencies, List<FederatedItemCreateRequest> newItems, List<FederatedItemDeleteRequest> deleteItems, List<FederatedItemUpdateRequest> updateItems)
    {
        return await StartTransaction(walletAddress, inventoryTransaction, operationName, new
        {
            currencies,
            newItems,
            deleteItems,
            updateItems
        });
    }

    public async Task AddChainTransaction(ChainTransaction chainTransaction)
    {
        if (_currentTransaction.Value.HasValue)
            await _transactionLogCollection.AddChainTransaction(_currentTransaction.Value!.Value, chainTransaction);
    }

    public async Task RunAsyncBlock(ObjectId transactionId, string? inventoryTransactionId, Func<Task> block, Func<Exception, Task>? onError = null)
    {
        try
        {
            await block();
            await TransactionDone(transactionId);
        }
        catch (Exception ex)
        {
            var error = $"Error processing transaction {transactionId}. Error: {ex.ToLogFormat()}";
            BeamableLogger.LogError(error);
            await TransactionError(transactionId, inventoryTransactionId, ex);
            if (onError is not null)
            {
                await onError(ex);
            }
            throw new TransactionException(error);
        }
    }

    private async Task<ObjectId> StartTransaction<TRequest>(string walletAddress, string? inventoryTransaction, string operationName, TRequest request)
    {
        return await StartTransaction(walletAddress, inventoryTransaction, operationName, request, _requestContext.UserId, _requestContext.Path);
    }

    private async Task<ObjectId> StartTransaction<TRequest>(string walletAddress, string? inventoryTransaction, string operationName, TRequest request, long requesterUserId, string path)
    {
        if (inventoryTransaction is not null)
        {
            var isSuccess = await _inventoryTransactionCollection.TryInsertInventoryTransaction(inventoryTransaction);
            if (!isSuccess) throw new TransactionException($"Inventory transaction {inventoryTransaction} already processed or in-progress");
        }

        var transactionId = ObjectId.GenerateNewId();
        await _transactionLogCollection.Insert(new TransactionLog
        {
            Id = transactionId,
            InventoryTransactionId = inventoryTransaction,
            RequesterUserId = requesterUserId,
            Wallet = walletAddress,
            Request = request as string ?? JsonSerializer.Serialize(request, JsonSerializerOptions),
            Path = path,
            OperationName = operationName
        });

        Interlocked.Increment(ref _inflightTransactions);

        return transactionId;
    }

    private async Task TransactionError(ObjectId transactionId, string? inventoryTransactionId, Exception ex)
    {
        Interlocked.Decrement(ref _inflightTransactions);
        if (inventoryTransactionId is not null)
        {
            BeamableLogger.Log("Clearing the inventory transaction {transactionId} record to enable retries.", inventoryTransactionId);
            await _inventoryTransactionCollection.DeleteInventoryTransaction(inventoryTransactionId);
        }
        await _transactionLogCollection.SetError(transactionId, ex.Message);
    }

    public async Task TransactionError(string transactionId, Exception ex)
    {
        Interlocked.Decrement(ref _inflightTransactions);
        var inventoryTransactionId = await _transactionLogCollection.GetInventoryTransaction(ObjectId.Parse(transactionId));
        if (!string.IsNullOrWhiteSpace(inventoryTransactionId))
        {
            BeamableLogger.Log("Clearing the inventory transaction {transactionId} record to enable retries.", inventoryTransactionId);
            await _inventoryTransactionCollection.DeleteInventoryTransaction(inventoryTransactionId);
        }
        await _transactionLogCollection.SetError(ObjectId.Parse(transactionId), ex.Message);
    }

    private async Task TransactionDone(ObjectId transactionId)
    {
        Interlocked.Decrement(ref _inflightTransactions);
        await _transactionLogCollection.SetDone(transactionId);
    }
}