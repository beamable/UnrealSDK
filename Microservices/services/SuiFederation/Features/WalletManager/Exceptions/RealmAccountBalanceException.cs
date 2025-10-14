using System.Net;
using Beamable.Server;

namespace Beamable.SuiFederation.Features.WalletManager.Exceptions;

public class RealmAccountBalanceException(string message)
    : MicroserviceException((int)HttpStatusCode.BadRequest, "RealmAccountBalanceException", message);