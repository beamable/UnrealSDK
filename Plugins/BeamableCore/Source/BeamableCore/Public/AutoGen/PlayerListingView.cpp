
#include "AutoGen/PlayerListingView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UPlayerListingView ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UClientDataEntry*>(TEXT("clientDataList"), ClientDataList, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("clientData"), ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cooldown"), &Cooldown, Serializer);
	Serializer->WriteValue(TEXT("secondsActive"), SecondsActive);
	UBeamJsonUtils::SerializeUObject<UPlayerOfferView*>("offer", Offer, Serializer);
	Serializer->WriteValue(TEXT("queryAfterPurchase"), bQueryAfterPurchase);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("purchasesRemain"), &PurchasesRemain, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemain"), &SecondsRemain, Serializer);
	Serializer->WriteValue(TEXT("active"), bActive);
}

void UPlayerListingView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UClientDataEntry*>(TEXT("clientDataList"), ClientDataList, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("clientData"), ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("cooldown"), &Cooldown, Serializer);
	Serializer->WriteValue(TEXT("secondsActive"), SecondsActive);
	UBeamJsonUtils::SerializeUObject<UPlayerOfferView*>("offer", Offer, Serializer);
	Serializer->WriteValue(TEXT("queryAfterPurchase"), bQueryAfterPurchase);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("purchasesRemain"), &PurchasesRemain, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemain"), &SecondsRemain, Serializer);
	Serializer->WriteValue(TEXT("active"), bActive);		
}

void UPlayerListingView ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UClientDataEntry*>(Bag->GetArrayField(TEXT("clientDataList")), ClientDataList, OuterOwner);
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("clientData")), ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("cooldown", Bag, Cooldown, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("secondsActive")), SecondsActive);
	UBeamJsonUtils::DeserializeUObject<UPlayerOfferView*>("offer", Bag, Offer, OuterOwner);
	bQueryAfterPurchase = Bag->GetBoolField(TEXT("queryAfterPurchase"));
	UBeamJsonUtils::DeserializeOptional<int32>("purchasesRemain", Bag, PurchasesRemain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("secondsRemain", Bag, SecondsRemain, OuterOwner);
	bActive = Bag->GetBoolField(TEXT("active"));
}