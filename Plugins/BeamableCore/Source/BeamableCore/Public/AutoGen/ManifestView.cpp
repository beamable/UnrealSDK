
#include "AutoGen/ManifestView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UManifestView ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("createdByAccountId"), CreatedByAccountId);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>(TEXT("storageReference"), &StorageReference, Serializer);
	UBeamJsonUtils::SerializeArray<UServiceReference*>(TEXT("manifest"), Manifest, Serializer);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);
}

void UManifestView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("createdByAccountId"), CreatedByAccountId);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>(TEXT("storageReference"), &StorageReference, Serializer);
	UBeamJsonUtils::SerializeArray<UServiceReference*>(TEXT("manifest"), Manifest, Serializer);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("comments"), &Comments, Serializer);		
}

void UManifestView ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("createdByAccountId")), CreatedByAccountId);
	Id = Bag->GetStringField(TEXT("id"));
	Checksum = Bag->GetStringField(TEXT("checksum"));
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceStorageReference*>, UServiceStorageReference*>("storageReference", Bag, StorageReference, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UServiceReference*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeOptional<FString>("comments", Bag, Comments, OuterOwner);
}