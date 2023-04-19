
#include "BeamableCore/Public/AutoGen/BeginPurchaseRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBeginPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("purchaseId"), PurchaseId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("time"), &Time, Serializer);
}

void UBeginPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("purchaseId"), PurchaseId);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("time"), &Time, Serializer);		
}

void UBeginPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	PurchaseId = Bag->GetStringField(TEXT("purchaseId"));
	UBeamJsonUtils::DeserializeOptional<FString>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("time", Bag, Time, OuterOwner);
}



