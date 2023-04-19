
#include "BeamableCore/Public/AutoGen/PromoteRealmResponseOld.h"
#include "Serialization/BeamJsonUtils.h"



void UPromoteRealmResponseOld::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPromoteRealmResponseOld::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sourcePid"), SourcePid);
	UBeamJsonUtils::SerializeArray<URealmPromotion*>(TEXT("promotions"), Promotions, Serializer);
}

void UPromoteRealmResponseOld::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sourcePid"), SourcePid);
	UBeamJsonUtils::SerializeArray<URealmPromotion*>(TEXT("promotions"), Promotions, Serializer);		
}

void UPromoteRealmResponseOld::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	SourcePid = Bag->GetStringField(TEXT("sourcePid"));
	UBeamJsonUtils::DeserializeArray<URealmPromotion*>(Bag->GetArrayField(TEXT("promotions")), Promotions, OuterOwner);
}



