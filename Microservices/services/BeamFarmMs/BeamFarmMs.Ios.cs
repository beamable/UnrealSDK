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
    
    [FederationId("gamecenter")]
    public class GameCenterFederation : IFederationId
    {
    }

    public partial class BeamFarmMs : IFederatedLogin<GameCenterFederation>
    {
     
        /// <summary>
        /// We're authenticating GameCenter users based on the userId provided by the client.
        /// We just return the userId provided by the client as GameCenter doesn't provide a way to verify the token on the server side.
        /// </summary>
        /// <param name="userId"></param>
        /// <param name="challenge"></param>
        /// <param name="solution"></param>
        /// <returns></returns>
        async Promise<FederatedAuthenticationResponse> IFederatedLogin<GameCenterFederation>.Authenticate(string userId, string challenge, string solution)
        {
            return new FederatedAuthenticationResponse()
            {
                user_id = userId
            };
        }
    }
}

