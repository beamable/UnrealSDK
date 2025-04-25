
#include "BeamableCore/Public/AutoGen/BeamoBasicURLResponse.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoBasicURLResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeArray<UUploadURL*>(TEXT("s3URLs"), S3URLs, Serializer);
}

void UBeamoBasicURLResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("serviceName"), ServiceName, Serializer);
	UBeamJsonUtils::SerializeArray<UUploadURL*>(TEXT("s3URLs"), S3URLs, Serializer);		
}

void UBeamoBasicURLResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("serviceName")), ServiceName);
	UBeamJsonUtils::DeserializeArray<UUploadURL*>(Bag->GetArrayField(TEXT("s3URLs")), S3URLs, OuterOwner);
}



