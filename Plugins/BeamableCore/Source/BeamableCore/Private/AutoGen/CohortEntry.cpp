
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
	Trial = Bag->GetStringField(TEXT("trial"));
	Cohort = Bag->GetStringField(TEXT("cohort"));
}



