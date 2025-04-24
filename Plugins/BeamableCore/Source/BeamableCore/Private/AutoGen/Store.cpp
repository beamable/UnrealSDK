
#include "BeamableCore/Public/AutoGen/Store.h"
#include "Serialization/BeamJsonUtils.h"




void UStore::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeArray<UListing*>(TEXT("listings"), Listings, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("showInactiveListings"), &bShowInactiveListings, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeListingLimit"), &ActiveListingLimit, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("choose"), &Choose, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("refreshTime"), &RefreshTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);
}

void UStore::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeArray<UListing*>(TEXT("listings"), Listings, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("showInactiveListings"), &bShowInactiveListings, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("activeListingLimit"), &ActiveListingLimit, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("choose"), &Choose, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("refreshTime"), &RefreshTime, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("title"), &Title, Serializer);		
}

void UStore::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeArray<UListing*>(Bag->GetArrayField(TEXT("listings")), Listings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("showInactiveListings", Bag, bShowInactiveListings, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("activeListingLimit", Bag, ActiveListingLimit, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("choose", Bag, Choose, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("refreshTime", Bag, RefreshTime, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("title", Bag, Title, OuterOwner);
}



