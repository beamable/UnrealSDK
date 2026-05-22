
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MutateRequestArgs.h"
#include "Serialization/BeamJsonUtils.h"




void UMutateRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UMutationInput*>(TEXT("inputs"), Inputs, Serializer);
}

void UMutateRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UMutationInput*>(TEXT("inputs"), Inputs, Serializer);		
}

void UMutateRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UMutationInput*>(TEXT("inputs"), Bag, Inputs, OuterOwner);
}



