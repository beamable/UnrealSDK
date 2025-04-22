
#include "BeamableCore/Public/AutoGen/UploadRequestFromPortal.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UUploadRequestFromPortal::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectKey"), ObjectKey, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sizeInBytes"), SizeInBytes, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("lastModified"), &LastModified, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UMetadataPair*>, UMetadataPair*>(TEXT("metadata"), &Metadata, Serializer);
}

void UUploadRequestFromPortal::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectKey"), ObjectKey, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sizeInBytes"), SizeInBytes, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("lastModified"), &LastModified, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UMetadataPair*>, UMetadataPair*>(TEXT("metadata"), &Metadata, Serializer);		
}

void UUploadRequestFromPortal::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("objectKey")), ObjectKey);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sizeInBytes")), SizeInBytes);
	UBeamJsonUtils::DeserializeOptional<int64>("lastModified", Bag, LastModified, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UMetadataPair*>, UMetadataPair*>("metadata", Bag, Metadata, OuterOwner);
}



