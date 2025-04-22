
#include "BeamableCore/Public/AutoGen/CohortEntry.h"





void UCohortEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("trial"), Trial, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cohort"), Cohort, Serializer);
}

void UCohortEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("trial"), Trial, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cohort"), Cohort, Serializer);		
}

void UCohortEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("trial")), Trial);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cohort")), Cohort);
}



