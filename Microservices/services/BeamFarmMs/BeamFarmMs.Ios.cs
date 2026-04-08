using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Linq;
using System.Net.Http;
using System.Security.Cryptography;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;
using Microsoft.IdentityModel.Tokens;
using Newtonsoft.Json.Linq;

namespace Beamable.BeamFarmMs
{
    [FederationId("apple")]
    public class AppleFederation : IFederationId
    {
    }

    public partial class BeamFarmMs : IFederatedLogin<AppleFederation>
    {
        private const string APPLE_ISSUER = "https://appleid.apple.com";
        private const string APPLE_KEYS_URL = "https://appleid.apple.com/auth/keys";

        async Promise<FederatedAuthenticationResponse> IFederatedLogin<AppleFederation>.Authenticate(
            string token,
            string challenge,
            string solution)
        {
            var payload = await ValidateAppleToken(token);

            return new FederatedAuthenticationResponse()
            {
                user_id = payload.Sub
            };
        }

        private async Promise<ApplePayload> ValidateAppleToken(string identityToken)
        {
            var handler = new JwtSecurityTokenHandler();
            var jwt = handler.ReadJwtToken(identityToken);

            var kid = jwt.Header.Kid;

            var keys = await GetAppleKeys();

            var key = keys.First(x => x.Kid == kid);

            var rsa = RSA.Create();
            rsa.ImportParameters(new RSAParameters
            {
                Modulus = Base64UrlEncoder.DecodeBytes(key.N),
                Exponent = Base64UrlEncoder.DecodeBytes(key.E)
            });

            var validationParameters = new TokenValidationParameters
            {
                ValidateIssuer = true,
                ValidIssuer = APPLE_ISSUER,

                ValidateAudience = false, // optional but recommended to enable

                ValidateLifetime = true,

                ValidateIssuerSigningKey = true,
                IssuerSigningKey = new RsaSecurityKey(rsa)
            };

            var principal = handler.ValidateToken(
                identityToken,
                validationParameters,
                out _
            );

            return new ApplePayload
            {
                Sub = principal.FindFirst("sub")?.Value,
                Email = principal.FindFirst("email")?.Value
            };
        }

        private async Promise<List<AppleKey>> GetAppleKeys()
        {
            using var client = new HttpClient();

            var json = await client.GetStringAsync(APPLE_KEYS_URL);

            var obj = JObject.Parse(json);

            return obj["keys"]
                .Select(k => new AppleKey
                {
                    Kid = k["kid"].ToString(),
                    N = k["n"].ToString(),
                    E = k["e"].ToString()
                })
                .ToList();
        }
    }

    public class AppleKey
    {
        public string Kid;
        public string N;
        public string E;
    }

    public class ApplePayload
    {
        public string Sub;
        public string Email;
    }
}

