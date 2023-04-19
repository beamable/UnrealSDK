
#include "BeamableCore/Public/AutoGen/EntitlementRequirement.h"
#include "Serialization/BeamJsonUtils.h"




void UEntitlementRequirement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("constraint"), Constraint);
	Serializer->WriteValue(TEXT("state"), State);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);
}

void UEntitlementRequirement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("constraint"), Constraint);
	Serializer->WriteValue(TEXT("state"), State);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("specialization"), &Specialization, Serializer);		
}

void UEntitlementRequirement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	Constraint = Bag->GetStringField(TEXT("constraint"));
	State = Bag->GetStringField(TEXT("state"));
	UBeamJsonUtils::DeserializeOptional<FString>("specialization", Bag, Specialization, OuterOwner);
}



