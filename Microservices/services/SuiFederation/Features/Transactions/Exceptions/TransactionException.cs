using System.Net;
using Beamable.Server;

namespace Beamable.SuiFederation.Features.Transactions.Exceptions;

public class TransactionException(string message) : MicroserviceException((int)HttpStatusCode.BadRequest, "TransactionException",
    message);