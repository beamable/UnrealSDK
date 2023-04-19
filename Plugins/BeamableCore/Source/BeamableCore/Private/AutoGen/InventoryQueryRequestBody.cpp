
#include "BeamableCore/Public/AutoGen/InventoryQueryRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UInventoryQueryRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);
}

void UInventoryQueryRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("scopes"), &Scopes, Serializer);		
}

void UInventoryQueryRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("scopes", Bag, Scopes, OuterOwner);
}



