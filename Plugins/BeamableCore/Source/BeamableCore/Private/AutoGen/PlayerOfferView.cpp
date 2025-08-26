
#include "BeamableCore/Public/AutoGen/PlayerOfferView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UPlayerOfferView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("coupons"), Coupons, Serializer);
	UBeamJsonUtils::SerializeUObject<UPrice*>("price", Price, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
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
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("coupons"), Coupons, Serializer);
	UBeamJsonUtils::SerializeUObject<UPrice*>("price", Price, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("coupons"), Bag, Coupons);
	UBeamJsonUtils::DeserializeUObject<UPrice*>("price", Bag, Price, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("symbol"), Bag, Symbol);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("titles"), Bag, Titles, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UItemCreateRequestBody*>(TEXT("obtainItems"), Bag, ObtainItems, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UCurrencyChange*>(TEXT("obtainCurrency"), Bag, ObtainCurrency, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("images"), Bag, Images, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("descriptions"), Bag, Descriptions, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("obtain"), Bag, Obtain, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("buttonText", Bag, ButtonText, OuterOwner);
}



