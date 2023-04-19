
#include "BeamableCore/Public/AutoGen/PlayerOfferView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UPlayerOfferView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("coupons"), Coupons);
	UBeamJsonUtils::SerializeUObject<UPrice*>("price", Price, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("titles"), Titles, Serializer);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("obtainItems"), ObtainItems, Serializer);
	UBeamJsonUtils::SerializeArray<UCurrencyChange*>(TEXT("obtainCurrency"), ObtainCurrency, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("images"), Images, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("descriptions"), Descriptions, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("obtain"), Obtain, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("buttonText"), &ButtonText, Serializer);
}

void UPlayerOfferView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("coupons"), Coupons);
	UBeamJsonUtils::SerializeUObject<UPrice*>("price", Price, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("titles"), Titles, Serializer);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("obtainItems"), ObtainItems, Serializer);
	UBeamJsonUtils::SerializeArray<UCurrencyChange*>(TEXT("obtainCurrency"), ObtainCurrency, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("images"), Images, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("descriptions"), Descriptions, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("obtain"), Obtain, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("buttonText"), &ButtonText, Serializer);		
}

void UPlayerOfferView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Coupons = Bag->GetIntegerField(TEXT("coupons"));
	UBeamJsonUtils::DeserializeUObject<UPrice*>("price", Bag, Price, OuterOwner);
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("titles")), Titles, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UItemCreateRequestBody*>(Bag->GetArrayField(TEXT("obtainItems")), ObtainItems, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UCurrencyChange*>(Bag->GetArrayField(TEXT("obtainCurrency")), ObtainCurrency, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("images")), Images, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("descriptions")), Descriptions, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("obtain")), Obtain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("buttonText", Bag, ButtonText, OuterOwner);
}



