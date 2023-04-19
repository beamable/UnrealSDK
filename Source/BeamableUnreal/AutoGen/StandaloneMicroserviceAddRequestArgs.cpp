
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceAddRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UStandaloneMicroserviceAddRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("a"), A);
	Serializer->WriteValue(TEXT("b"), B);
}

void UStandaloneMicroserviceAddRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("a"), A);
	Serializer->WriteValue(TEXT("b"), B);		
}

void UStandaloneMicroserviceAddRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	A = Bag->GetIntegerField(TEXT("a"));
	B = Bag->GetIntegerField(TEXT("b"));
}



