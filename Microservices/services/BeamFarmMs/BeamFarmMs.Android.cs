using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Threading.Tasks;
using Beamable.Common;
using Newtonsoft.Json.Linq;

namespace Beamable.BeamFarmMs
{
	[FederationId("google")]
	public class GoogleFederation : IFederationId
	{
		
	}
	
	public partial class BeamFarmMs : IFederatedLogin<GoogleFederation>
	{
		/// <summary>
		/// We are validating the token provided by the client by calling Google's token verification endpoint and return the userId (sub) provided in the response as the authenticated userId.
		/// </summary>
		/// <param name="token"></param>
		/// <param name="challenge"></param>
		/// <param name="solution"></param>
		/// <returns></returns>
		async Promise<FederatedAuthenticationResponse> IFederatedLogin<GoogleFederation>.Authenticate(string token, string challenge, string solution)
		{
			return new FederatedAuthenticationResponse()
			{
				user_id = await GetGoogleUidFromIdTokenAsync(token)
			};
		}
		
		/// <summary>
		/// Token validation is done by calling Google's token verification endpoint and passing the token provided by the client. If the token is valid, we return the userId (sub) provided in the response as the authenticated userId.
		/// </summary>
		/// <param name="idToken"></param>
		/// <returns></returns>
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
