
#include "BeamableCore/Public/AutoGen/CohortEntry.h"





void UCohortEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("trial"), Trial);
	Serializer->WriteValue(TEXT("cohort"), Cohort);
}

void UCohortEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("trial"), Trial);
	Serializer->WriteValue(TEXT("cohort"), Cohort);		
}

void UCohortEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("trial")), Trial);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("cohort")), Cohort);
}



