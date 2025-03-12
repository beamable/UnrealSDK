using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Text;
using System.Text.Json;
using Beamable.Common.Api.Auth;
using Beamable.Server;

namespace Beamable.SuiFederation.Extensions;

public static class RequestContextExtensions
{
	private const string HeaderEncodedRc = "x-obj-rc";
	private const string RcExternalField = "external";
	private const string RcAccountIdField = "accountId";
	private const string HeaderExternal = "external";
	private const string HeaderAccountId = "aid";

	private static readonly JsonSerializerOptions JsonSerializerOptions = new()
	{
		IncludeFields = true
	};

	public static IEnumerable<ExternalIdentity> GetExternalIdentities(this RequestContext requestContext)
	{
		try
		{
			if (requestContext.Headers.TryGetValue(HeaderEncodedRc, out var encodedRc))
			{
				var rcBytes = Convert.FromBase64String(encodedRc);
				var rcString = Encoding.UTF8.GetString(rcBytes);
				var rcMap = JsonSerializer.Deserialize<Dictionary<string, object>>(rcString);
				if (rcMap is not null && rcMap.TryGetValue(RcExternalField, out var externalList))
				{
					var externalListJson = externalList.ToString();
					if (!string.IsNullOrEmpty(externalListJson))
						return JsonSerializer.Deserialize<List<ExternalIdentity>>(externalListJson, JsonSerializerOptions) ?? Enumerable.Empty<ExternalIdentity>();
				}
			}

			if (requestContext.Headers.TryGetValue(HeaderExternal, out var externalListLegacy))
			{
				if (!string.IsNullOrEmpty(externalListLegacy))
					return JsonSerializer.Deserialize<List<ExternalIdentity>>(externalListLegacy, JsonSerializerOptions) ?? Enumerable.Empty<ExternalIdentity>();
			}

			return [];
		}
		catch (Exception ex)
		{
			throw new RequestContextParsingException(ex.Message);
		}
	}

	public static ExternalIdentity? GetExternalIdentity(this RequestContext requestContext, MicroserviceInfo microserviceInfo)
	{
		var externalIdentities = requestContext.GetExternalIdentities();
		var existingExternalIdentity = externalIdentities
			.FirstOrDefault(x => x.providerService == microserviceInfo.MicroserviceName && x.providerNamespace == microserviceInfo.MicroserviceNamespace);
		return existingExternalIdentity;
	}

	public static long? GetAccountId(this RequestContext requestContext)
	{
		try
		{
			if (requestContext.Headers.TryGetValue(HeaderEncodedRc, out var encodedRc))
			{
				var rcBytes = Convert.FromBase64String(encodedRc);
				var rcString = Encoding.UTF8.GetString(rcBytes);
				var rcMap = JsonSerializer.Deserialize<Dictionary<string, object>>(rcString);

				if (rcMap is not null)
				{
					rcMap.TryGetValue(RcAccountIdField, out var accountIdObject);
					if (accountIdObject is JsonElement { ValueKind: JsonValueKind.Number } a)
					{
						return a.GetInt64();
					}
				}
			}

			requestContext.Headers.TryGetValue(HeaderAccountId, out var accountIdString);
			if (long.TryParse(accountIdString, out var parsedAccountId))
			{
				return parsedAccountId;
			}

			return null;
		}
		catch (Exception ex)
		{
			throw new RequestContextParsingException(ex.Message);
		}
	}

	private class RequestContextParsingException(string message)
		: MicroserviceException((int)HttpStatusCode.BadRequest, "RequestContextParsingError", message);
}