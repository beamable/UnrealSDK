
#include "BeamableCore/Public/AutoGen/GetStoresReq.h"
#include "Serialization/BeamJsonUtils.h"




void UGetStoresReq::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
}

void UGetStoresReq::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);		
}

void UGetStoresReq::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("scope", Bag, Scope, OuterOwner);
}



