using System.Text.Json.Serialization;

namespace Beamable.SuiFederation.Features.Contract.SuiClientWrapper.Models;

public class KeyToolConvert
{
    [JsonPropertyName("bech32WithFlag")]
    public string Bench32Format { get; set; } = null!;

    [JsonPropertyName("base64WithFlag")]
    public string Base64Format { get; set; } = null!;

    [JsonPropertyName("hexWithoutFlag")]
    public string HexFormat { get; set; } = null!;

    [JsonPropertyName("scheme")]
    public string Scheme { get; set; } = null!;
}