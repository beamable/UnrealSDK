#include "BeamBackend/BeamCustomRequests.h"

#include "Misc/DefaultValueHelper.h"

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


void ULoginRefreshTokenRequest::BuildVerb(FString& VerbString) const { VerbString = TEXT("POST"); }

void ULoginRefreshTokenRequest::BuildRoute(FString& RouteString) const { RouteString.Appendf(TEXT("/basic/auth/token")); }

void ULoginRefreshTokenRequest::BuildBody(FString& BodyString) const
{
	TUnrealJsonSerializer Serializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&BodyString);
	Serializer->WriteObjectStart();
	Serializer->WriteValue(TEXT("grant_type"), GrantType);
	Serializer->WriteValue(TEXT("refresh_token"), RefreshToken);
	Serializer->WriteObjectEnd();
	Serializer->Close();
}

void ULoginRefreshTokenResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Body->BeamSerializeProperties(Serializer);
}

void ULoginRefreshTokenResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Body->BeamSerializeProperties(Serializer);
}

void ULoginRefreshTokenResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Body = NewObject<UTokenResponse>(OuterOwner.GetEvenIfUnreachable());
	Body->BeamDeserializeProperties(Bag);
}
