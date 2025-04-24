
#include "BeamableCore/Public/AutoGen/BeamoBasicReference.h"





void UBeamoBasicReference::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("archived"), bArchived, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("arm"), bArm, Serializer);
}

void UBeamoBasicReference::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("archived"), bArchived, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("arm"), bArm, Serializer);		
}

void UBeamoBasicReference::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("archived")), bArchived);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("arm")), bArm);
}



