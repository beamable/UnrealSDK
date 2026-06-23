
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetSlotStatesRequestArgs.h"
#include "Serialization/BeamJsonUtils.h"




void UGetSlotStatesRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("slotIds"), SlotIds, Serializer);
}

void UGetSlotStatesRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("slotIds"), SlotIds, Serializer);		
}

void UGetSlotStatesRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("slotIds"), Bag, SlotIds, OuterOwner);
}



