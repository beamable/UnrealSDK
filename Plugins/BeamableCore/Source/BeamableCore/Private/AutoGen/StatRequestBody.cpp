
#include "BeamableCore/Public/AutoGen/StatRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UStatRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("stats"), &Stats, Serializer);
}

void UStatRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("stats"), &Stats, Serializer);		
}

void UStatRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("stats", Bag, Stats, OuterOwner);
}



