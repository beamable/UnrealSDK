
#include "BeamableCore/Public/AutoGen/PlayerStoreView.h"
#include "Serialization/BeamJsonUtils.h"




void UPlayerStoreView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerListingView*>(TEXT("listings"), Listings, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("nextDeltaSeconds"), &NextDeltaSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemain"), &SecondsRemain, Serializer);
}

void UPlayerStoreView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeArray<UPlayerListingView*>(TEXT("listings"), Listings, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("nextDeltaSeconds"), &NextDeltaSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemain"), &SecondsRemain, Serializer);		
}

void UPlayerStoreView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeArray<UPlayerListingView*>(Bag->GetArrayField(TEXT("listings")), Listings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("nextDeltaSeconds", Bag, NextDeltaSeconds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("title", Bag, Title, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("secondsRemain", Bag, SecondsRemain, OuterOwner);
}



