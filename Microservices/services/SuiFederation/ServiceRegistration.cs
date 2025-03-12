using System.Linq;
using System.Reflection;
using Beamable.Common.Dependencies;
using Beamable.SuiFederation.Extensions;
using Beamable.SuiFederation.Features.Transactions;

namespace Beamable.SuiFederation;

public static class ServiceRegistration
{
    public static void AddFeatures(this IDependencyBuilder builder)
    {
        Assembly.GetExecutingAssembly()
            .GetDerivedTypes<IService>()
            .ToList()
            .ForEach(serviceType => builder.AddSingleton(serviceType));

        builder.AddScoped<TransactionManager>();
    }
}