#include "RawAPIs/BeamSharedTypes.h"

#include "BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void FTokenResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("access_token"), AccessToken);
	Serializer->WriteValue(TEXT("token_type"), TokenType);
	Serializer->WriteValue(TEXT("refresh_token"), RefreshToken);
	Serializer->WriteValue(TEXT("expires_in"), ExpiresIn);	
}

void FTokenResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	AccessToken = Bag->GetStringField(TEXT("access_token"));
	TokenType = Bag->GetStringField(TEXT("token_type"));
	RefreshToken = Bag->GetStringField(TEXT("refresh_token"));	
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("expires_in")), ExpiresIn);	
}

/**

  _____   ____   _____ _______   _                 _         _____       __               _       _______    _              
 |  __ \ / __ \ / ____|__   __| | |               (_)       |  __ \     / _|             | |     |__   __|  | |             
 | |__) | |  | | (___    | |    | |     ___   __ _ _ _ __   | |__) |___| |_ _ __ ___  ___| |__      | | ___ | | _____ _ __  
 |  ___/| |  | |\___ \   | |    | |    / _ \ / _` | | '_ \  |  _  // _ \  _| '__/ _ \/ __| '_ \     | |/ _ \| |/ / _ \ '_ \ 
 | |    | |__| |____) |  | |    | |___| (_) | (_| | | | | | | | \ \  __/ | | | |  __/\__ \ | | |    | | (_) |   <  __/ | | |
 |_|     \____/|_____/   |_|    |______\___/ \__, |_|_| |_| |_|  \_\___|_| |_|  \___||___/_| |_|    |_|\___/|_|\_\___|_| |_|
											  __/ |                                                                         
											 |___/                                                                          

 */

void FLoginRefreshTokenRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("grant_type"), GrantType);
	Serializer->WriteValue(TEXT("refresh_token"), RefreshToken);
}

void FLoginRefreshTokenRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	GrantType = Bag->GetStringField(TEXT("grant_type"));
	RefreshToken = Bag->GetStringField(TEXT("refresh_token"));
}

void FLoginRefreshTokenRequest::BuildVerb(FString& VerbString) const { VerbString = TEXT("POST"); }

void FLoginRefreshTokenRequest::BuildRoute(FString& RouteString) const { RouteString.Appendf(TEXT("/basic/auth/token")); }

void FLoginRefreshTokenRequest::BuildBody(FString& BodyString) const
{
	TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&BodyString);
	Body.BeamSerialize(JsonSerializer);
	JsonSerializer->Close();
}
