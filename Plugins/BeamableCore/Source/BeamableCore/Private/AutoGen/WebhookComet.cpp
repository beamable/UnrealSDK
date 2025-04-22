
#include "BeamableCore/Public/AutoGen/WebhookComet.h"
#include "Serialization/BeamJsonUtils.h"




void UWebhookComet::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("method"), Method, Serializer);
	UBeamJsonUtils::SerializeUObject<URouteVariables*>("variables", Variables, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeUObject<UServiceRoute*>("route", Route, Serializer);
	UBeamJsonUtils::SerializeUObject<URouteParameters*>("parameters", Parameters, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);
}

void UWebhookComet::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("method"), Method, Serializer);
	UBeamJsonUtils::SerializeUObject<URouteVariables*>("variables", Variables, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("symbol"), Symbol, Serializer);
	UBeamJsonUtils::SerializeUObject<UServiceRoute*>("route", Route, Serializer);
	UBeamJsonUtils::SerializeUObject<URouteParameters*>("parameters", Parameters, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("description"), &Description, Serializer);		
}

void UWebhookComet::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("method")), Method);
	UBeamJsonUtils::DeserializeUObject<URouteVariables*>("variables", Bag, Variables, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("symbol")), Symbol);
	UBeamJsonUtils::DeserializeUObject<UServiceRoute*>("route", Bag, Route, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<URouteParameters*>("parameters", Bag, Parameters, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("description", Bag, Description, OuterOwner);
}



