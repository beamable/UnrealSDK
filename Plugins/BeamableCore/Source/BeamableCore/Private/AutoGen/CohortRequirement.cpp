
#include "BeamableCore/Public/AutoGen/CohortRequirement.h"





void UCohortRequirement::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("trial"), Trial, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cohort"), Cohort, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("constraint"), Constraint, Serializer);
}

void UCohortRequirement::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("trial"), Trial, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cohort"), Cohort, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("constraint"), Constraint, Serializer);		
}

void UCohortRequirement::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("trial")), Trial);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cohort")), Cohort);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("constraint")), Constraint);
}



