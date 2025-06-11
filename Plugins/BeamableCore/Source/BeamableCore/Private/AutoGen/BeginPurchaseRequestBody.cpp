
#include "BeamableCore/Public/AutoGen/BeginPurchaseRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBeginPurchaseRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("purchaseId"), PurchaseId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("time"), &Time, Serializer);
}

void UBeginPurchaseRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("purchaseId"), PurchaseId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("time"), &Time, Serializer);		
}

void UBeginPurchaseRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("purchaseId")), PurchaseId);
	UBeamJsonUtils::DeserializeOptional<FString>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("time", Bag, Time, OuterOwner);
}



