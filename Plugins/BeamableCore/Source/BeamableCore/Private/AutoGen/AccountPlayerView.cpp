
#include "BeamableCore/Public/AutoGen/AccountPlayerView.h"
#include "Serialization/BeamJsonUtils.h"



void UAccountPlayerView::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAccountPlayerView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("deviceIds"), DeviceIds, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("thirdPartyAppAssociations"), ThirdPartyAppAssociations, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>(TEXT("external"), &External, Serializer);
}

void UAccountPlayerView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("deviceIds"), DeviceIds, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("scopes"), Scopes, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("thirdPartyAppAssociations"), ThirdPartyAppAssociations, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>(TEXT("external"), &External, Serializer);		
}

void UAccountPlayerView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<int64>(TEXT("id"), Bag, Id, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("deviceIds"), Bag, DeviceIds, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("scopes"), Bag, Scopes, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("thirdPartyAppAssociations"), Bag, ThirdPartyAppAssociations, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>("external", Bag, External, OuterOwner);
}



