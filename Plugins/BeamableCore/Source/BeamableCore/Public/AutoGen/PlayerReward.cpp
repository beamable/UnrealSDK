
#include "AutoGen/PlayerReward.h"
#include "Serialization/BeamJsonUtils.h"


void UPlayerReward ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("addItemRequests"), AddItemRequests, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyChangeReward*>, UCurrencyChangeReward*>(TEXT("changeCurrencies"), &ChangeCurrencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UWebhookReward*>, UWebhookReward*>(TEXT("callWebhooks"), &CallWebhooks, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UNewItemReward*>, UNewItemReward*>(TEXT("addItems"), &AddItems, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("applyVipBonus"), &bApplyVipBonus, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("addCurrencyMap"), AddCurrencyMap, Serializer);
}

void UPlayerReward::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeArray<UItemCreateRequestBody*>(TEXT("addItemRequests"), AddItemRequests, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyChangeReward*>, UCurrencyChangeReward*>(TEXT("changeCurrencies"), &ChangeCurrencies, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UWebhookReward*>, UWebhookReward*>(TEXT("callWebhooks"), &CallWebhooks, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UNewItemReward*>, UNewItemReward*>(TEXT("addItems"), &AddItems, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("applyVipBonus"), &bApplyVipBonus, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("addCurrencyMap"), AddCurrencyMap, Serializer);		
}

void UPlayerReward ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UItemCreateRequestBody*>(Bag->GetArrayField(TEXT("addItemRequests")), AddItemRequests, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UCurrencyChangeReward*>, UCurrencyChangeReward*>("changeCurrencies", Bag, ChangeCurrencies, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UWebhookReward*>, UWebhookReward*>("callWebhooks", Bag, CallWebhooks, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UNewItemReward*>, UNewItemReward*>("addItems", Bag, AddItems, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("applyVipBonus", Bag, bApplyVipBonus, OuterOwner);
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("addCurrencyMap")), AddCurrencyMap, OuterOwner);
}