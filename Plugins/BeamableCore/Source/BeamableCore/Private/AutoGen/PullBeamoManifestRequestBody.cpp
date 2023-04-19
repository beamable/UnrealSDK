
#include "BeamableCore/Public/AutoGen/PullBeamoManifestRequestBody.h"





void UPullBeamoManifestRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sourceRealmPid"), SourceRealmPid);
}

void UPullBeamoManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sourceRealmPid"), SourceRealmPid);		
}

void UPullBeamoManifestRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	SourceRealmPid = Bag->GetStringField(TEXT("sourceRealmPid"));
}



