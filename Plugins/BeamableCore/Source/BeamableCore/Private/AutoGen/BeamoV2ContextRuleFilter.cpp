
#include "BeamableCore/Public/AutoGen/BeamoV2ContextRuleFilter.h"
#include "Serialization/BeamJsonUtils.h"




void UBeamoV2ContextRuleFilter::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<EBeamBeamoV2RuleOperationType>(TEXT("playerIdOperationType"), &PlayerIdOperationType, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamBeamoV2RuleOperationType>(TEXT("pathsOperationType"), &PathsOperationType, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<int64>, int64>(TEXT("playerIds"), &PlayerIds, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("paths"), &Paths, Serializer);
}

void UBeamoV2ContextRuleFilter::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<EBeamBeamoV2RuleOperationType>(TEXT("playerIdOperationType"), &PlayerIdOperationType, Serializer);
	UBeamJsonUtils::SerializeOptional<EBeamBeamoV2RuleOperationType>(TEXT("pathsOperationType"), &PathsOperationType, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<int64>, int64>(TEXT("playerIds"), &PlayerIds, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("paths"), &Paths, Serializer);
}

void UBeamoV2ContextRuleFilter::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<EBeamBeamoV2RuleOperationType>("playerIdOperationType", Bag, PlayerIdOperationType, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<EBeamBeamoV2RuleOperationType>("pathsOperationType", Bag, PathsOperationType, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<int64>, int64>("playerIds", Bag, PlayerIds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("paths", Bag, Paths, OuterOwner);
}



