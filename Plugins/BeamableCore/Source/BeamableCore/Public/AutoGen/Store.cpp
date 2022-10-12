
#include "AutoGen/Store.h"
#include "Serialization/BeamJsonUtils.h"


void UStore ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeListingLimit"), &ActiveListingLimit, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("choose"), &Choose, Serializer);
	UBeamJsonUtils::SerializeArray<UListing*>(TEXT("listings"), Listings, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("showInactiveListings"), &bShowInactiveListings, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("refreshTime"), &RefreshTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);
}

void UStore::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeListingLimit"), &ActiveListingLimit, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("choose"), &Choose, Serializer);
	UBeamJsonUtils::SerializeArray<UListing*>(TEXT("listings"), Listings, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("showInactiveListings"), &bShowInactiveListings, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("refreshTime"), &RefreshTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);		
}

void UStore ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int32>("activeListingLimit", Bag, ActiveListingLimit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("choose", Bag, Choose, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UListing*>(Bag->GetArrayField(TEXT("listings")), Listings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("showInactiveListings", Bag, bShowInactiveListings, OuterOwner);
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeOptional<int32>("refreshTime", Bag, RefreshTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("title", Bag, Title, OuterOwner);
}