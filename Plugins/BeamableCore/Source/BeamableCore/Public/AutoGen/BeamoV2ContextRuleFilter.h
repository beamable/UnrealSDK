#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfInt64.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2RuleOperationType.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"

#include "BeamoV2ContextRuleFilter.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2ContextRuleFilter : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id Operation Type", Category="Beam")
	FOptionalBeamoV2RuleOperationType PlayerIdOperationType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Paths Operation Type", Category="Beam")
	FOptionalBeamoV2RuleOperationType PathsOperationType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Ids", Category="Beam")
	FOptionalArrayOfInt64 PlayerIds = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Paths", Category="Beam")
	FOptionalArrayOfString Paths = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};