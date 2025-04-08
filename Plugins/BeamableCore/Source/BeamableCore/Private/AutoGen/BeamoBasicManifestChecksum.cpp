
#include "BeamableCore/Public/AutoGen/BeamoBasicManifestChecksum.h"

#include "Misc/DefaultValueHelper.h"



void UBeamoBasicManifestChecksum::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("createdAt"), CreatedAt);
}

void UBeamoBasicManifestChecksum::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("createdAt"), CreatedAt);		
}

void UBeamoBasicManifestChecksum::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("checksum")), Checksum);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("createdAt")), CreatedAt);
}



