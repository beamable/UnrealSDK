
#include "BeamableCore/Public/AutoGen/AuthV2JsonWebKeySet.h"
#include "Serialization/BeamJsonUtils.h"



void UAuthV2JsonWebKeySet::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAuthV2JsonWebKeySet::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UAuthV2JsonWebKey*>, UAuthV2JsonWebKey*>(TEXT("keys"), &Keys, Serializer);
}

void UAuthV2JsonWebKeySet::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<UAuthV2JsonWebKey*>, UAuthV2JsonWebKey*>(TEXT("keys"), &Keys, Serializer);		
}

void UAuthV2JsonWebKeySet::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<UAuthV2JsonWebKey*>, UAuthV2JsonWebKey*>("keys", Bag, Keys, OuterOwner);
}



