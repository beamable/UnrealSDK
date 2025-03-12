using System.Collections.Generic;
using System.Linq;
using System.Text.Json.Serialization;
using Beamable.SuiFederation.Features.Contract.SuiClientWrapper.Exceptions;

namespace Beamable.SuiFederation.Features.Contract.SuiClientWrapper.Models;

public class MoveDeployOutput
{
    [JsonPropertyName("objectChanges")]
    public List<CreatedObjectsOutput> CreatedObjects { get; set; } = [];

    public class CreatedObjectsOutput
    {
        [JsonPropertyName("digest")] public string Digest { get; set; } = "";

        [JsonPropertyName("objectId")] public string ObjectId { get; set; } = "";

        [JsonPropertyName("objectType")] public string ObjectType { get; set; } = "";
        [JsonPropertyName("packageId")] public string PackageId { get; set; } = "";
    }
}

public static class MoveDeployOutputExtensions
{
    public static string GetPackageId(this MoveDeployOutput moveDeployOutput)
     => moveDeployOutput.CreatedObjects.FirstOrDefault(obj => !string.IsNullOrWhiteSpace(obj.PackageId))?.PackageId
        ?? throw new SuiClientException("PackageId not found.");
}