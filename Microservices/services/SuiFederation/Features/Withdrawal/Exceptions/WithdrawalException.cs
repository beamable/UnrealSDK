using System.Net;
using Beamable.Server;

namespace Beamable.SuiFederation.Features.Withdrawal.Exceptions;

public class WithdrawalException(string message)
    : MicroserviceException((int)HttpStatusCode.BadRequest, "WithdrawalException", message);