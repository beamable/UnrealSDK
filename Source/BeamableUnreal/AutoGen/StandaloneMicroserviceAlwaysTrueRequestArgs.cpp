
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceAlwaysTrueRequestArgs.h"





void UStandaloneMicroserviceAlwaysTrueRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("text"), Text);
}

void UStandaloneMicroserviceAlwaysTrueRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("text"), Text);		
}

void UStandaloneMicroserviceAlwaysTrueRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Text = Bag->GetStringField(TEXT("text"));
}



