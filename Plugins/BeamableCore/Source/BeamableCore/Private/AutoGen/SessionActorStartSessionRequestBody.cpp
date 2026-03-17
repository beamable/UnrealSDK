
#include "BeamableCore/Public/AutoGen/SessionActorStartSessionRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USessionActorStartSessionRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("source"), &Source, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("locale"), &Locale, Serializer);
	UBeamJsonUtils::SerializeOptional<USessionLanguageContextDto*>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("customParams"), &CustomParams, Serializer);
}

void USessionActorStartSessionRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("source"), &Source, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("locale"), &Locale, Serializer);
	UBeamJsonUtils::SerializeOptional<USessionLanguageContextDto*>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("customParams"), &CustomParams, Serializer);		
}

void USessionActorStartSessionRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("platform", Bag, Platform, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("device", Bag, Device, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("source", Bag, Source, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("locale", Bag, Locale, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<USessionLanguageContextDto*>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("customParams", Bag, CustomParams, OuterOwner);
}



