
#include "BeamableCore/Public/AutoGen/BeamoV2PromoteBeamoManifestRequestBody.h"





void UBeamoV2PromoteBeamoManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourceRealmId"), SourceRealmId, Serializer);
}

void UBeamoV2PromoteBeamoManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourceRealmId"), SourceRealmId, Serializer);		
}

void UBeamoV2PromoteBeamoManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sourceRealmId")), SourceRealmId);
}



