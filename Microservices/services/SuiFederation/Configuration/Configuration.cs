using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Net;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;
using Beamable.Server.Api.RealmConfig;

namespace Beamable.SuiFederation;

public class Configuration : IService
{
    private const string ConfigurationNamespace = "sui-federation";
    private readonly IRealmConfigService _realmConfigService;

    public readonly string RealmSecret = Environment.GetEnvironmentVariable("SECRET") ?? "";
    private RealmConfig? _realmConfig;

    public Configuration(IRealmConfigService realmConfigService, SocketRequesterContext socketRequesterContext)
    {
        _realmConfigService = realmConfigService;
        socketRequesterContext.Subscribe<object>(Constants.Features.Services.REALM_CONFIG_UPDATE_EVENT, _ =>
        {
            BeamableLogger.Log("Realm config was updated");
            _realmConfig = null;
        });
    }

    /// <summary>
    /// CONFIG VALUES
    /// To configure an explicit configuration values, visit the Beamable portal and add configuration under Operate -> Config.
    /// Configuration namespace is configured in the <see cref="ConfigurationNamespace"/> constant.
    /// </summary>

    public ValueTask<string> SuiEnvironment => GetValue(nameof(SuiEnvironment), "devnet");
    public ValueTask<int> AuthenticationChallengeTtlSec => GetValue(nameof(AuthenticationChallengeTtlSec), 600);

    private async ValueTask<T> GetValue<T>(string key, T defaultValue) where T : IConvertible
    {
        _realmConfig ??= await _realmConfigService.GetRealmConfigSettings();
        var namespaceConfig = _realmConfig!.GetValueOrDefault(ConfigurationNamespace) ?? new ReadOnlyDictionary<string, string>(new Dictionary<string, string>());
        var value = namespaceConfig.GetValueOrDefault(key);
        if (value is null)
        {
            return defaultValue;
        }
        return (T)Convert.ChangeType(value, typeof(T));
    }
}

internal class ConfigurationException(string message)
    : MicroserviceException((int)HttpStatusCode.BadRequest, "ConfigurationError", message);