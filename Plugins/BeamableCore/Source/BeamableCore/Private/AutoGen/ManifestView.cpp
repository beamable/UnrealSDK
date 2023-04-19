
#include "BeamableCore/Public/AutoGen/ManifestView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UManifestView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeArray<UServiceReference*>(TEXT("manifest"), Manifest, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdByAccountId"), &CreatedByAccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>(TEXT("storageReference"), &StorageReference, Serializer);
}

void UManifestView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeArray<UServiceReference*>(TEXT("manifest"), Manifest, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdByAccountId"), &CreatedByAccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>(TEXT("storageReference"), &StorageReference, Serializer);		
}

void UManifestView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	Checksum = Bag->GetStringField(TEXT("checksum"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeArray<UServiceReference*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdByAccountId", Bag, CreatedByAccountId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>("storageReference", Bag, StorageReference, OuterOwner);
}



