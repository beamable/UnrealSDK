using System;
using HandlebarsDotNet;
using SuiFederationCommon.Extensions;

namespace Beamable.SuiFederation.Features.Contract;

public static class ContractTemplateService
{
    private static bool _initialized;
    public static void Initialize()
    {
        if (_initialized) return;

        Handlebars.RegisterHelper("toUpperCase", (writer, _, parameters) =>
            WriteTransformed(writer, parameters, s => FederationContentExtensions.SanitizeModuleName(s).ToUpperInvariant()));

        Handlebars.RegisterHelper("toLowerCase", (writer, _, parameters) =>
            WriteTransformed(writer, parameters, s => FederationContentExtensions.SanitizeModuleName(s).ToLowerInvariant()));

        Handlebars.RegisterHelper("toStructName", (writer, _, parameters) =>
            WriteTransformed(writer, parameters, s =>
            {
                var cleaned = FederationContentExtensions.SanitizeModuleName(s);
                return string.IsNullOrEmpty(cleaned) ? cleaned
                    : char.ToUpperInvariant(cleaned[0]) + cleaned[1..];
            }));
        _initialized = true;
    }

    private static void WriteTransformed(EncodedTextWriter writer, Arguments parameters, Func<string, string> transform)
    {
        if (parameters.Length > 0 && parameters[0] is string input)
        {
            writer.Write(transform(input));
        }
    }
}