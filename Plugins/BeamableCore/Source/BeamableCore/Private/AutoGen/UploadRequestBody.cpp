
#include "BeamableCore/Public/AutoGen/UploadRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UUploadRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectKey"), ObjectKey, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sizeInBytes"), SizeInBytes, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("deleted"), &bDeleted, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("lastModified"), &LastModified, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UMetadataPair*>, UMetadataPair*>(TEXT("metadata"), &Metadata, Serializer);
}

void UUploadRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("objectKey"), ObjectKey, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sizeInBytes"), SizeInBytes, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("deleted"), &bDeleted, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("lastModified"), &LastModified, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UMetadataPair*>, UMetadataPair*>(TEXT("metadata"), &Metadata, Serializer);		
}

void UUploadRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("objectKey")), ObjectKey);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("sizeInBytes")), SizeInBytes);
	UBeamJsonUtils::DeserializeOptional<bool>("deleted", Bag, bDeleted, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("lastModified", Bag, LastModified, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UMetadataPair*>, UMetadataPair*>("metadata", Bag, Metadata, OuterOwner);
}



