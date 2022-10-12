
#include "AutoGen/GetStatusResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UGetStatusResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServiceStatus*>(TEXT("services"), Services, Serializer);
	Serializer->WriteValue(TEXT("isCurrent"), bIsCurrent);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageStatus*>, UServiceStorageStatus*>(TEXT("storageStatuses"), &StorageStatuses, Serializer);
}

void UGetStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UServiceStatus*>(TEXT("services"), Services, Serializer);
	Serializer->WriteValue(TEXT("isCurrent"), bIsCurrent);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageStatus*>, UServiceStorageStatus*>(TEXT("storageStatuses"), &StorageStatuses, Serializer);		
}

void UGetStatusResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UServiceStatus*>(Bag->GetArrayField(TEXT("services")), Services, OuterOwner);
	bIsCurrent = Bag->GetBoolField(TEXT("isCurrent"));
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceStorageStatus*>, UServiceStorageStatus*>("storageStatuses", Bag, StorageStatuses, OuterOwner);
}