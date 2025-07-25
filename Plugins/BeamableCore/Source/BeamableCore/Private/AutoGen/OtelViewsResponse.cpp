
#include "BeamableCore/Public/AutoGen/OtelViewsResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UOtelViewsResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UOtelViewsResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UOtelView*>(TEXT("views"), Views, Serializer);
}

void UOtelViewsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UOtelView*>(TEXT("views"), Views, Serializer);		
}

void UOtelViewsResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UOtelView*>(Bag->GetArrayField(TEXT("views")), Views, OuterOwner);
}



