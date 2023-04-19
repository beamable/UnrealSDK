
#include "BeamableCore/Public/AutoGen/GetOffersReq.h"
#include "Serialization/BeamJsonUtils.h"




void UGetOffersReq::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("time"), &Time, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("stores"), &Stores, Serializer);
}

void UGetOffersReq::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("time"), &Time, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("stores"), &Stores, Serializer);		
}

void UGetOffersReq::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("time", Bag, Time, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("stores", Bag, Stores, OuterOwner);
}



