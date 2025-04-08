
#include "BeamableCore/Public/AutoGen/CohortRequirement.h"





void UCohortRequirement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("trial"), Trial);
	Serializer->WriteValue(TEXT("cohort"), Cohort);
	Serializer->WriteValue(TEXT("constraint"), Constraint);
}

void UCohortRequirement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("trial"), Trial);
	Serializer->WriteValue(TEXT("cohort"), Cohort);
	Serializer->WriteValue(TEXT("constraint"), Constraint);		
}

void UCohortRequirement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("trial")), Trial);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cohort")), Cohort);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("constraint")), Constraint);
}



