
#include "AutoGen/UploadRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UUploadRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("objectKey"), ObjectKey);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("lastModified"), &LastModified, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	Serializer->WriteValue(TEXT("sizeInBytes"), SizeInBytes);
	UBeamJsonUtils::SerializeOptional<TArray<UMetadataPair*>, UMetadataPair*>(TEXT("metadata"), &Metadata, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("deleted"), &bDeleted, Serializer);
}

void UUploadRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("objectKey"), ObjectKey);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("lastModified"), &LastModified, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("checksum"), &Checksum, Serializer);
	Serializer->WriteValue(TEXT("sizeInBytes"), SizeInBytes);
	UBeamJsonUtils::SerializeOptional<TArray<UMetadataPair*>, UMetadataPair*>(TEXT("metadata"), &Metadata, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("deleted"), &bDeleted, Serializer);		
}

void UUploadRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ObjectKey = Bag->GetStringField(TEXT("objectKey"));
	UBeamJsonUtils::DeserializeOptional<int64>("lastModified", Bag, LastModified, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("checksum", Bag, Checksum, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("sizeInBytes")), SizeInBytes);
	UBeamJsonUtils::DeserializeOptional<TArray<UMetadataPair*>, UMetadataPair*>("metadata", Bag, Metadata, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("deleted", Bag, bDeleted, OuterOwner);
}