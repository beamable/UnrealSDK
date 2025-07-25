
#include "BeamableCore/Public/AutoGen/InventoryView.h"
#include "Serialization/BeamJsonUtils.h"



void UInventoryView::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UInventoryView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCurrencyView*>(TEXT("currencies"), Currencies, Serializer);
	UBeamJsonUtils::SerializeArray<UItemGroup*>(TEXT("items"), Items, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);
}

void UInventoryView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCurrencyView*>(TEXT("currencies"), Currencies, Serializer);
	UBeamJsonUtils::SerializeArray<UItemGroup*>(TEXT("items"), Items, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("scope"), &Scope, Serializer);		
}

void UInventoryView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UCurrencyView*>(TEXT("currencies"), Bag, Currencies, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UItemGroup*>(TEXT("items"), Bag, Items, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("scope", Bag, Scope, OuterOwner);
}



