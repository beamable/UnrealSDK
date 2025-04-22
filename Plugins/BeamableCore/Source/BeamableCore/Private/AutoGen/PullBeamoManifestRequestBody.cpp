
#include "BeamableCore/Public/AutoGen/PullBeamoManifestRequestBody.h"





void UPullBeamoManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourceRealmPid"), SourceRealmPid, Serializer);
}

void UPullBeamoManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourceRealmPid"), SourceRealmPid, Serializer);		
}

void UPullBeamoManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sourceRealmPid")), SourceRealmPid);
}



