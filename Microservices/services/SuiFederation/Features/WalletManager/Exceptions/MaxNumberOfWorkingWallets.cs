using System.Net;
using Beamable.Server;

namespace Beamable.SuiFederation.Features.WalletManager.Exceptions;

public class MaxNumberOfWorkingWallets()
    : MicroserviceException((int)HttpStatusCode.BadRequest, "MaxNumberOfWorkingWallets", "");