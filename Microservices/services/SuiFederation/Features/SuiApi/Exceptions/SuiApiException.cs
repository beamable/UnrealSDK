using System.Net;
using Beamable.Server;

namespace Beamable.SuiFederation.Features.SuiApi.Exceptions;

public class SuiApiException(string message) : MicroserviceException((int)HttpStatusCode.BadRequest, "SuiApiException",
    message);