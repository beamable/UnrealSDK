
#include "BeamableCore/Public/AutoGen/GetStatusResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetStatusResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetStatusResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isCurrent"), bIsCurrent);
	UBeamJsonUtils::SerializeArray<UServiceStatus*>(TEXT("services"), Services, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageStatus*>, UServiceStorageStatus*>(TEXT("storageStatuses"), &StorageStatuses, Serializer);
}

void UGetStatusResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("isCurrent"), bIsCurrent);
	UBeamJsonUtils::SerializeArray<UServiceStatus*>(TEXT("services"), Services, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UServiceStorageStatus*>, UServiceStorageStatus*>(TEXT("storageStatuses"), &StorageStatuses, Serializer);		
}

void UGetStatusResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bIsCurrent = Bag->GetBoolField(TEXT("isCurrent"));
	UBeamJsonUtils::DeserializeArray<UServiceStatus*>(Bag->GetArrayField(TEXT("services")), Services, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UServiceStorageStatus*>, UServiceStorageStatus*>("storageStatuses", Bag, StorageStatuses, OuterOwner);
}



