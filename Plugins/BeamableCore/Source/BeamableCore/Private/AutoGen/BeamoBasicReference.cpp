
#include "BeamableCore/Public/AutoGen/BeamoBasicReference.h"





void UBeamoBasicReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("archived"), bArchived);
	Serializer->WriteValue(TEXT("arm"), bArm);
}

void UBeamoBasicReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("archived"), bArchived);
	Serializer->WriteValue(TEXT("arm"), bArm);		
}

void UBeamoBasicReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bArchived = Bag->GetBoolField(TEXT("archived"));
	bArm = Bag->GetBoolField(TEXT("arm"));
}



