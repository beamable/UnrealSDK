
#include "BeamableCore/Public/AutoGen/GetStatusResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetStatusResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetStatusResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isCurrent"), bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeArray<UServiceStatus*>(TEXT("services"), Services, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageStatus*>, UServiceStorageStatus*>(TEXT("storageStatuses"), &StorageStatuses, Serializer);
}

void UGetStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("isCurrent"), bIsCurrent, Serializer);
	UBeamJsonUtils::SerializeArray<UServiceStatus*>(TEXT("services"), Services, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageStatus*>, UServiceStorageStatus*>(TEXT("storageStatuses"), &StorageStatuses, Serializer);		
}

void UGetStatusResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("isCurrent"), Bag, bIsCurrent);
	UBeamJsonUtils::DeserializeArray<UServiceStatus*>(TEXT("services"), Bag, Services, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceStorageStatus*>, UServiceStorageStatus*>("storageStatuses", Bag, StorageStatuses, OuterOwner);
}



