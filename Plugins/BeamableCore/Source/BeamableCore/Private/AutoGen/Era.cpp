
#include "BeamableCore/Public/AutoGen/Era.h"

#include "Misc/DefaultValueHelper.h"



void UEra::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("value"), Value);
}

void UEra::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("value"), Value);		
}

void UEra::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Value = Bag->GetIntegerField(TEXT("value"));
}



