
#include "BeamableCore/Public/AutoGen/UpdateData.h"
#include "Serialization/BeamJsonUtils.h"




void UUpdateData::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deletes"), &Deletes, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("updates"), &Updates, Serializer);
}

void UUpdateData::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deletes"), &Deletes, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("updates"), &Updates, Serializer);		
}

void UUpdateData::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("deletes", Bag, Deletes, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("updates", Bag, Updates, OuterOwner);
}



