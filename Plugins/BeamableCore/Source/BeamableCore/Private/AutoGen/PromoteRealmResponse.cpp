
#include "BeamableCore/Public/AutoGen/PromoteRealmResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UPromoteRealmResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UPromoteRealmResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourcePid"), &SourcePid, Serializer);
	UBeamJsonUtils::SerializeArray<UPromotionScope*>(TEXT("scopes"), Scopes, Serializer);
}

void UPromoteRealmResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("sourcePid"), &SourcePid, Serializer);
	UBeamJsonUtils::SerializeArray<UPromotionScope*>(TEXT("scopes"), Scopes, Serializer);		
}

void UPromoteRealmResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("sourcePid")), SourcePid, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UPromotionScope*>(Bag->GetArrayField(TEXT("scopes")), Scopes, OuterOwner);
}



