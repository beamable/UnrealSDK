using System.Threading.Tasks;
using Beamable.SuiFederation.Features.LockManager.Storage;

namespace Beamable.SuiFederation.Features.LockManager;

public class LockManagerService(LockCollection lockCollection) : IService
{
    public async Task<bool> AcquireLock(string lockName, int lockTimeoutSeconds = 0)
    {
        return await lockCollection.AcquireLock(lockName, lockTimeoutSeconds);
    }

    public async Task ReleaseLock(string lockName)
    {
        await lockCollection.ReleaseLock(lockName);
    }
}