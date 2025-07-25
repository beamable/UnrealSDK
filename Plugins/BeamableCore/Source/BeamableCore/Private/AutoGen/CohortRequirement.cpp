
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("trial"), Bag, Trial);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("cohort"), Bag, Cohort);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("constraint"), Bag, Constraint);
}



