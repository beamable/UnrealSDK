
#include "BeamableCore/Public/AutoGen/OfferConstraint.h"

#include "Misc/DefaultValueHelper.h"



void UOfferConstraint::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("constraint"), Constraint);
	Serializer->WriteValue(TEXT("value"), Value);
}

void UOfferConstraint::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("constraint"), Constraint);
	Serializer->WriteValue(TEXT("value"), Value);		
}

void UOfferConstraint::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Constraint = Bag->GetStringField(TEXT("constraint"));
	Value = Bag->GetIntegerField(TEXT("value"));
}



