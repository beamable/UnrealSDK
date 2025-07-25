
#include "BeamableCore/Public/AutoGen/BeamoBasicManifestChecksum.h"

#include "Misc/DefaultValueHelper.h"



void UBeamoBasicManifestChecksum::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdAt"), CreatedAt, Serializer);
}

void UBeamoBasicManifestChecksum::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("checksum"), Checksum, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdAt"), CreatedAt, Serializer);		
}

void UBeamoBasicManifestChecksum::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("checksum"), Bag, Checksum);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("createdAt"), Bag, CreatedAt);
}



