
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceJoinNumbersAsStringRequestArgs.h"

#include "Misc/DefaultValueHelper.h"



void UStandaloneMicroserviceJoinNumbersAsStringRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("a"), A);
	Serializer->WriteValue(TEXT("b"), B);
}

void UStandaloneMicroserviceJoinNumbersAsStringRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("a"), A);
	Serializer->WriteValue(TEXT("b"), B);		
}

void UStandaloneMicroserviceJoinNumbersAsStringRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	A = Bag->GetIntegerField(TEXT("a"));
	B = Bag->GetIntegerField(TEXT("b"));
}



