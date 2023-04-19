
#include "BeamableCore/Public/AutoGen/Period.h"
#include "Serialization/BeamJsonUtils.h"




void UPeriod::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("start"), Start);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end"), &End, Serializer);
}

void UPeriod::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("start"), Start);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("end"), &End, Serializer);		
}

void UPeriod::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Start = Bag->GetStringField(TEXT("start"));
	UBeamJsonUtils::DeserializeOptional<FString>("end", Bag, End, OuterOwner);
}



