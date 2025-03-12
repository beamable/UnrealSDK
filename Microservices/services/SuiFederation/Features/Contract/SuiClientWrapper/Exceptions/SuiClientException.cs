using System.Net;
using Beamable.Server;

namespace Beamable.SuiFederation.Features.Contract.SuiClientWrapper.Exceptions;

public class SuiClientException(string message) : MicroserviceException((int)HttpStatusCode.BadRequest, "SuiClientException",
    message);