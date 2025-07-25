
#include "BeamableCore/Public/AutoGen/PromoteRealmResponseOld.h"
#include "Serialization/BeamJsonUtils.h"



void UPromoteRealmResponseOld::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPromoteRealmResponseOld::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourcePid"), SourcePid, Serializer);
	UBeamJsonUtils::SerializeArray<URealmPromotion*>(TEXT("promotions"), Promotions, Serializer);
}

void UPromoteRealmResponseOld::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourcePid"), SourcePid, Serializer);
	UBeamJsonUtils::SerializeArray<URealmPromotion*>(TEXT("promotions"), Promotions, Serializer);		
}

void UPromoteRealmResponseOld::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("sourcePid"), Bag, SourcePid);
	UBeamJsonUtils::DeserializeArray<URealmPromotion*>(TEXT("promotions"), Bag, Promotions, OuterOwner);
}



