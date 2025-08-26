
#include "BeamableCore/Public/AutoGen/PlayerListingView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UPlayerListingView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("active"), bActive, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("queryAfterPurchase"), bQueryAfterPurchase, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("secondsActive"), SecondsActive, Serializer);
	UBeamJsonUtils::SerializeUObject<UPlayerOfferView*>("offer", Offer, Serializer);
	UBeamJsonUtils::SerializeArray<UClientDataEntry*>(TEXT("clientDataList"), ClientDataList, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("clientData"), ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cooldown"), &Cooldown, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("purchasesRemain"), &PurchasesRemain, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemain"), &SecondsRemain, Serializer);
}

void UPlayerListingView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("active"), bActive, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("queryAfterPurchase"), bQueryAfterPurchase, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("secondsActive"), SecondsActive, Serializer);
	UBeamJsonUtils::SerializeUObject<UPlayerOfferView*>("offer", Offer, Serializer);
	UBeamJsonUtils::SerializeArray<UClientDataEntry*>(TEXT("clientDataList"), ClientDataList, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("clientData"), ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cooldown"), &Cooldown, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("purchasesRemain"), &PurchasesRemain, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemain"), &SecondsRemain, Serializer);		
}

void UPlayerListingView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("active"), Bag, bActive);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("queryAfterPurchase"), Bag, bQueryAfterPurchase);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("symbol"), Bag, Symbol);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("secondsActive"), Bag, SecondsActive);
	UBeamJsonUtils::DeserializeUObject<UPlayerOfferView*>("offer", Bag, Offer, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UClientDataEntry*>(TEXT("clientDataList"), Bag, ClientDataList, OuterOwner);
	UBeamJsonUtils::DeserializeMap<FString>(TEXT("clientData"), Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("cooldown", Bag, Cooldown, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("purchasesRemain", Bag, PurchasesRemain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("secondsRemain", Bag, SecondsRemain, OuterOwner);
}



