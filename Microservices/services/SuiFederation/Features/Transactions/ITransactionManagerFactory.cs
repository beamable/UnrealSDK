namespace Beamable.SuiFederation.Features.Transactions;

public interface ITransactionManagerFactory
{
    TransactionManager Create(string transactionId);
}