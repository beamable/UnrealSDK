
#include "BeamableCore/Public/AutoGen/OrderRules.h"
#include "Serialization/BeamJsonUtils.h"




void UOrderRules::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UOrderRule*>(TEXT("orules"), Orules, Serializer);
}

void UOrderRules::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UOrderRule*>(TEXT("orules"), Orules, Serializer);		
}

void UOrderRules::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UOrderRule*>(Bag->GetArrayField(TEXT("orules")), Orules, OuterOwner);
}



