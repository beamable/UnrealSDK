using System.Threading.Tasks;
using Beamable.SuiFederation.Features.LockManager.Storage;

namespace Beamable.SuiFederation.Features.LockManager;

public class LockManagerService : IService
{
    private readonly LockCollection _lockCollection;

    public LockManagerService(LockCollection lockCollection)
    {
        _lockCollection = lockCollection;
    }

    public async Task<bool> AcquireLock(string lockName, int lockTimeoutSeconds = 10 * 60)
    {
        return await _lockCollection.AcquireLock(lockName, lockTimeoutSeconds);
    }

    public async Task ReleaseLock(string lockName)
    {
        await _lockCollection.ReleaseLock(lockName);
    }
}