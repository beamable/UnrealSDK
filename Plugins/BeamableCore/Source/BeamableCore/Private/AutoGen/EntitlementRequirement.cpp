
#include "BeamableCore/Public/AutoGen/EntitlementRequirement.h"
#include "Serialization/BeamJsonUtils.h"




void UEntitlementRequirement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("constraint"), Constraint, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("state"), State, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);
}

void UEntitlementRequirement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("constraint"), Constraint, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("state"), State, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);		
}

void UEntitlementRequirement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("symbol"), Bag, Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("constraint"), Bag, Constraint);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("state"), Bag, State);
	UBeamJsonUtils::DeserializeOptional<FString>("specialization", Bag, Specialization, OuterOwner);
}



