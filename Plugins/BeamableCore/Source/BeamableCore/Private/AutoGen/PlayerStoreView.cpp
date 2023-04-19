
#include "BeamableCore/Public/AutoGen/PlayerStoreView.h"
#include "Serialization/BeamJsonUtils.h"




void UPlayerStoreView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeArray<UPlayerListingView*>(TEXT("listings"), Listings, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("nextDeltaSeconds"), &NextDeltaSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemain"), &SecondsRemain, Serializer);
}

void UPlayerStoreView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeArray<UPlayerListingView*>(TEXT("listings"), Listings, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("nextDeltaSeconds"), &NextDeltaSeconds, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("secondsRemain"), &SecondsRemain, Serializer);		
}

void UPlayerStoreView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeArray<UPlayerListingView*>(Bag->GetArrayField(TEXT("listings")), Listings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("nextDeltaSeconds", Bag, NextDeltaSeconds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("title", Bag, Title, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("secondsRemain", Bag, SecondsRemain, OuterOwner);
}



