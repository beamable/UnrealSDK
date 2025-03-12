using System.Net;
using Beamable.Server;

namespace Beamable.SuiFederation.Features.Contract.Exceptions;

public class ContractException(string message) : MicroserviceException((int)HttpStatusCode.BadRequest, "ContractException",
    message);