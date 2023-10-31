
#include "BeamableCore/Public/AutoGen/BeamoBasicURLResponse.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoBasicURLResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	UBeamJsonUtils::SerializeArray<UUploadURL*>(TEXT("s3URLs"), S3URLs, Serializer);
}

void UBeamoBasicURLResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("serviceName"), ServiceName);
	UBeamJsonUtils::SerializeArray<UUploadURL*>(TEXT("s3URLs"), S3URLs, Serializer);		
}

void UBeamoBasicURLResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ServiceName = Bag->GetStringField(TEXT("serviceName"));
	UBeamJsonUtils::DeserializeArray<UUploadURL*>(Bag->GetArrayField(TEXT("s3URLs")), S3URLs, OuterOwner);
}



