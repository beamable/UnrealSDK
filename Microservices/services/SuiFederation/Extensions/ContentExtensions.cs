using Beamable.Common.Api.Auth;
using Beamable.Common.Content;

namespace Beamable.SuiFederation.Extensions;

public static class ContentExtensions
{
    public static bool Matches(this OptionalFederation federation, ExternalIdentity externalIdentity)
        => federation.HasValue && federation.Value.Service == externalIdentity.providerService &&
           federation.Value.Namespace == externalIdentity.providerNamespace;
}