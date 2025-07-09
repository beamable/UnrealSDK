
#include "BeamableCore/Public/AutoGen/PromoteBeamoManifestRequestBody.h"





void UPromoteBeamoManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourceRealmId"), SourceRealmId, Serializer);
}

void UPromoteBeamoManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourceRealmId"), SourceRealmId, Serializer);		
}

void UPromoteBeamoManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sourceRealmId")), SourceRealmId);
}



