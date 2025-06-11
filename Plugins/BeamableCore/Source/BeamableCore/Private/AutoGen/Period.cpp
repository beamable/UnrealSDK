
#include "BeamableCore/Public/AutoGen/Period.h"
#include "Serialization/BeamJsonUtils.h"




void UPeriod::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("start"), Start, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end"), &End, Serializer);
}

void UPeriod::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("start"), Start, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end"), &End, Serializer);		
}

void UPeriod::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("start")), Start);
	UBeamJsonUtils::DeserializeOptional<FString>("end", Bag, End, OuterOwner);
}



