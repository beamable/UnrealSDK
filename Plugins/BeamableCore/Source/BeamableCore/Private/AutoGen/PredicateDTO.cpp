
#include "BeamableCore/Public/AutoGen/PredicateDTO.h"
#include "Serialization/BeamJsonUtils.h"




void UPredicateDTO::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("kind"), Kind, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("as"), &As, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("caseInsensitive"), &bCaseInsensitive, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("includeLower"), &bIncludeLower, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("includeUpper"), &bIncludeUpper, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lower"), &Lower, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("upper"), &Upper, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("substr"), &Substr, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("values"), &Values, Serializer);
}

void UPredicateDTO::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("kind"), Kind, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("as"), &As, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("caseInsensitive"), &bCaseInsensitive, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("includeLower"), &bIncludeLower, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("includeUpper"), &bIncludeUpper, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("lower"), &Lower, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("upper"), &Upper, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("substr"), &Substr, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("value"), &Value, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("values"), &Values, Serializer);		
}

void UPredicateDTO::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("kind"), Bag, Kind);
	UBeamJsonUtils::DeserializeOptional<FString>("as", Bag, As, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("caseInsensitive", Bag, bCaseInsensitive, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("includeLower", Bag, bIncludeLower, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("includeUpper", Bag, bIncludeUpper, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("lower", Bag, Lower, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("upper", Bag, Upper, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("substr", Bag, Substr, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("value", Bag, Value, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("values", Bag, Values, OuterOwner);
}



