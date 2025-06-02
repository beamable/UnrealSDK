using Beamable.Common.Dependencies;

namespace Beamable.SuiFederation.Endpoints;

public static class ServiceRegistration
{
    public static void AddEndpoints(this IDependencyBuilder builder)
    {
        builder.AddScoped<AuthenticateEndpoint>();
        builder.AddScoped<StartInventoryTransactionEndpoint>();
        builder.AddScoped<GetInventoryStateEndpoint>();
        builder.AddScoped<AuthenticateExternalEndpoint>();
    }
}