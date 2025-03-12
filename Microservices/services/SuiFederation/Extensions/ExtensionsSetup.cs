using Beamable.Server;

namespace Beamable.SuiFederation.Extensions;

public static class ExtensionsSetup
{
    public static void SetupExtensions(this IServiceInitializer initializer)
    {
        initializer.SetupMongoExtensions();
    }
}