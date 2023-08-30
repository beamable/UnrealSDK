
#include "BeamableCore/Public/AutoGen/UpdateParty.h"
#include "Serialization/BeamJsonUtils.h"




void UUpdateParty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxSize"), &MaxSize, Serializer);
}

void UUpdateParty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("restriction"), &Restriction, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("maxSize"), &MaxSize, Serializer);		
}

void UUpdateParty::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("restriction", Bag, Restriction, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("maxSize", Bag, MaxSize, OuterOwner);
}



