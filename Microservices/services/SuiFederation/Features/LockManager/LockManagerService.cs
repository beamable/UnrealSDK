using System.Collections.Generic;
using System.Threading.Tasks;
using Beamable.SuiFederation.Features.LockManager.Storage;
using Beamable.SuiFederation.Features.Transactions;

namespace Beamable.SuiFederation.Features.LockManager;

public class LockManagerService : IService
{
    private readonly LockCollection _lockCollection;

    public LockManagerService(LockCollection lockCollection)
    {
        _lockCollection = lockCollection;
    }

    public async Task<bool> AcquireLock(string lockName, int lockTimeoutSeconds = 60)
    {
        return await _lockCollection.AcquireLock(lockName, TransactionManager.InstanceId, lockTimeoutSeconds);
    }

    public async Task ReleaseLock(string lockName)
    {
        await _lockCollection.ReleaseLock(lockName);
    }

    public async Task<List<string>> GetLocked()
    {
        return await _lockCollection.GetLocked();
    }
}