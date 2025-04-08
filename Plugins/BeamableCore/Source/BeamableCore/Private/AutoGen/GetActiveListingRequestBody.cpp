
#include "BeamableCore/Public/AutoGen/GetActiveListingRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetActiveListingRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("listing"), Listing);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("store"), &Store, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("time"), &Time, Serializer);
}

void UGetActiveListingRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("listing"), Listing);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("store"), &Store, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("time"), &Time, Serializer);		
}

void UGetActiveListingRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("listing")), Listing);
	UBeamJsonUtils::DeserializeOptional<FString>("store", Bag, Store, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("time", Bag, Time, OuterOwner);
}



