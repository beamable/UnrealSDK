using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Threading.Tasks;
using Beamable.Common;
using Beamable.Server;
using Newtonsoft.Json.Linq;

namespace Beamable.BeamFarmMs
{
	[FederationId("google")]
	public class GoogleFederation : IFederationId
	{
		
	}
	
	public partial class BeamFarmMs : IFederatedLogin<GoogleFederation>, IFederatedLogin<AppleFederation>
	{
		async Promise<FederatedAuthenticationResponse> IFederatedLogin<GoogleFederation>.Authenticate(string token, string challenge, string solution)
		{
			return new FederatedAuthenticationResponse()
			{
				user_id = await GetGoogleUidFromIdTokenAsync(token)
			};
		}
		
		public async Task<string> GetGoogleUidFromIdTokenAsync(string idToken)
		{
			try
			{
				HttpClient httpClient = new HttpClient();
				
				var payload = new FormUrlEncodedContent(new[]
				{
					new KeyValuePair<string, string>("id_token", idToken)
				});

				// Google token verification endpoint
				var response = await httpClient.PostAsync(
					"https://oauth2.googleapis.com/tokeninfo", payload);

				response.EnsureSuccessStatusCode();

				var content = await response.Content.ReadAsStringAsync();

				// Parse the response to get the UID (sub)
				var json = JObject.Parse(content);
				var googleUid = json["sub"]?.ToString();

				return googleUid;
			}
			catch (Exception ex)
			{
				// Handle errors
				Console.WriteLine($"Error verifying token: {ex.Message}");
				throw;
			}
		}
	}
}
