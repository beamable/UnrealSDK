
#include "AutoGen/WebhookComet.h"
#include "Serialization/BeamJsonUtils.h"


void UWebhookComet ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("method"), Method);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeUObject<URouteVariables*>("variables", Variables, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeUObject<UServiceRoute*>("route", Route, Serializer);
	UBeamJsonUtils::SerializeUObject<URouteParameters*>("parameters", Parameters, Serializer);
}

void UWebhookComet::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("method"), Method);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
	UBeamJsonUtils::SerializeUObject<URouteVariables*>("variables", Variables, Serializer);
	Serializer->WriteValue(TEXT("symbol"), Symbol);
	UBeamJsonUtils::SerializeUObject<UServiceRoute*>("route", Route, Serializer);
	UBeamJsonUtils::SerializeUObject<URouteParameters*>("parameters", Parameters, Serializer);		
}

void UWebhookComet ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Method = Bag->GetStringField(TEXT("method"));
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<URouteVariables*>("variables", Bag, Variables, OuterOwner);
	Symbol = Bag->GetStringField(TEXT("symbol"));
	UBeamJsonUtils::DeserializeUObject<UServiceRoute*>("route", Bag, Route, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<URouteParameters*>("parameters", Bag, Parameters, OuterOwner);
}