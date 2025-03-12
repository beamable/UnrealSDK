using System.Text.Json.Serialization;

namespace Beamable.SuiFederation.Features.Contract.SuiClientWrapper.Models;

public class GasBalanceItem
{
    [JsonPropertyName("gasCoinId")] public string GasCoinId { get; set; } = "";

    [JsonPropertyName("mistBalance")]
    public long GasBalance { get; set; }
}