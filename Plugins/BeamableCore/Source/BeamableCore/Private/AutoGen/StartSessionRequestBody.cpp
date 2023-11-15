
#include "BeamableCore/Public/AutoGen/StartSessionRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStartSessionRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("source"), &Source, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("locale"), &Locale, Serializer);
	UBeamJsonUtils::SerializeOptional<USessionLanguageContext*>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("time"), &Time, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamer"), &Gamer, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("customParams"), &CustomParams, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("deviceParams"), &DeviceParams, Serializer);
}

void UStartSessionRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("source"), &Source, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("locale"), &Locale, Serializer);
	UBeamJsonUtils::SerializeOptional<USessionLanguageContext*>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("time"), &Time, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("platform"), &Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("gamer"), &Gamer, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("device"), &Device, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("customParams"), &CustomParams, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("deviceParams"), &DeviceParams, Serializer);		
}

void UStartSessionRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("source", Bag, Source, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("shard", Bag, Shard, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("locale", Bag, Locale, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<USessionLanguageContext*>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("time", Bag, Time, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("platform", Bag, Platform, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("gamer", Bag, Gamer, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("device", Bag, Device, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("customParams", Bag, CustomParams, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("deviceParams", Bag, DeviceParams, OuterOwner);
}



