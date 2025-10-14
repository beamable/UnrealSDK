using System.Net;
using Beamable.Server;

namespace Beamable.SuiFederation.Features.WalletManager.Exceptions;

public class NoWorkingWalletsException()
    : MicroserviceException((int)HttpStatusCode.BadRequest, "NoWorkingWalletsException", "");