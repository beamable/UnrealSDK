
#include "BeamableCore/Public/AutoGen/TokenRequestWrapper.h"
#include "Serialization/BeamJsonUtils.h"




void UTokenRequestWrapper::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("grant_type"), GrantType, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("customerScoped"), &bCustomerScoped, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device_id"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_service"), &ProviderService, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("token"), &Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("code"), &Code, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("external_token"), &ExternalToken, Serializer);
	UBeamJsonUtils::SerializeOptional<UChallengeSolution*>(TEXT("challenge_solution"), &ChallengeSolution, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("redirect_uri"), &RedirectUri, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("third_party"), &ThirdParty, Serializer);
	UBeamJsonUtils::SerializeOptional<UContextInfo*>(TEXT("context"), &Context, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refresh_token"), &RefreshToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("username"), &Username, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("client_id"), &ClientId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("initProperties"), &InitProperties, Serializer);
}

void UTokenRequestWrapper::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("grant_type"), GrantType, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("customerScoped"), &bCustomerScoped, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device_id"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_service"), &ProviderService, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("token"), &Token, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("code"), &Code, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("external_token"), &ExternalToken, Serializer);
	UBeamJsonUtils::SerializeOptional<UChallengeSolution*>(TEXT("challenge_solution"), &ChallengeSolution, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("provider_namespace"), &ProviderNamespace, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("redirect_uri"), &RedirectUri, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("third_party"), &ThirdParty, Serializer);
	UBeamJsonUtils::SerializeOptional<UContextInfo*>(TEXT("context"), &Context, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("refresh_token"), &RefreshToken, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("username"), &Username, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("client_id"), &ClientId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scope"), &Scope, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("initProperties"), &InitProperties, Serializer);		
}

void UTokenRequestWrapper::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("grant_type")), GrantType);
	UBeamJsonUtils::DeserializeOptional<bool>("customerScoped", Bag, bCustomerScoped, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("device_id", Bag, DeviceId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("provider_service", Bag, ProviderService, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("token", Bag, Token, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("code", Bag, Code, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("external_token", Bag, ExternalToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UChallengeSolution*>("challenge_solution", Bag, ChallengeSolution, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("provider_namespace", Bag, ProviderNamespace, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("redirect_uri", Bag, RedirectUri, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("third_party", Bag, ThirdParty, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UContextInfo*>("context", Bag, Context, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("refresh_token", Bag, RefreshToken, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("username", Bag, Username, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("client_id", Bag, ClientId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("password", Bag, Password, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("scope", Bag, Scope, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("initProperties", Bag, InitProperties, OuterOwner);
}



