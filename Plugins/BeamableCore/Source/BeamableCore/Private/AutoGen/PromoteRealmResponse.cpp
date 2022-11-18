
#include "AutoGen/PromoteRealmResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UPromoteRealmResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPromoteRealmResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sourcePid"), SourcePid);
	UBeamJsonUtils::SerializeArray<UPromotionScope*>(TEXT("scopes"), Scopes, Serializer);
}

void UPromoteRealmResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("sourcePid"), SourcePid);
	UBeamJsonUtils::SerializeArray<UPromotionScope*>(TEXT("scopes"), Scopes, Serializer);		
}

void UPromoteRealmResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	SourcePid = Bag->GetStringField(TEXT("sourcePid"));
	UBeamJsonUtils::DeserializeArray<UPromotionScope*>(Bag->GetArrayField(TEXT("scopes")), Scopes, OuterOwner);
}