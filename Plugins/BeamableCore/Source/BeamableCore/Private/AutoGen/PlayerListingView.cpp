
#include "BeamableCore/Public/AutoGen/PlayerListingView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UPlayerListingView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("active"), bActive);
	Serializer->WriteValue(TEXT("queryAfterPurchase"), bQueryAfterPurchase);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("secondsActive"), SecondsActive);
	UBeamJsonUtils::SerializeUObject<UPlayerOfferView*>("offer", Offer, Serializer);
	UBeamJsonUtils::SerializeArray<UClientDataEntry*>(TEXT("clientDataList"), ClientDataList, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("clientData"), ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cooldown"), &Cooldown, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("purchasesRemain"), &PurchasesRemain, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemain"), &SecondsRemain, Serializer);
}

void UPlayerListingView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("active"), bActive);
	Serializer->WriteValue(TEXT("queryAfterPurchase"), bQueryAfterPurchase);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	Serializer->WriteValue(TEXT("secondsActive"), SecondsActive);
	UBeamJsonUtils::SerializeUObject<UPlayerOfferView*>("offer", Offer, Serializer);
	UBeamJsonUtils::SerializeArray<UClientDataEntry*>(TEXT("clientDataList"), ClientDataList, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("clientData"), ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cooldown"), &Cooldown, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("purchasesRemain"), &PurchasesRemain, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemain"), &SecondsRemain, Serializer);		
}

void UPlayerListingView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bActive = Bag->GetBoolField(TEXT("active"));
	bQueryAfterPurchase = Bag->GetBoolField(TEXT("queryAfterPurchase"));
	Symbol = Bag->GetStringField(TEXT("symbol"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("secondsActive")), SecondsActive);
	UBeamJsonUtils::DeserializeUObject<UPlayerOfferView*>("offer", Bag, Offer, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UClientDataEntry*>(Bag->GetArrayField(TEXT("clientDataList")), ClientDataList, OuterOwner);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("clientData")), ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("cooldown", Bag, Cooldown, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("purchasesRemain", Bag, PurchasesRemain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("secondsRemain", Bag, SecondsRemain, OuterOwner);
}



