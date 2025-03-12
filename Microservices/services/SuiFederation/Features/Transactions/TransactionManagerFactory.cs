using System;
using Beamable.Common.Dependencies;
using Microsoft.Extensions.DependencyInjection;

namespace Beamable.SuiFederation.Features.Transactions;

public class TransactionManagerFactory(IDependencyProvider serviceProvider) : IService, ITransactionManagerFactory
{
    public TransactionManager Create(string transactionId)
    {
        var transactionManager = serviceProvider.GetRequiredService<TransactionManager>();
        transactionManager.SetCurrentTransactionContext(transactionId);
        return transactionManager;
    }
}