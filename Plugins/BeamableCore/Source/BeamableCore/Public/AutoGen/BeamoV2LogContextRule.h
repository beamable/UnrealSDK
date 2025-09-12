#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/BeamoV2LogContextRuleAuthor.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"
#include "BeamableCore/Public/AutoGen/Enums/BeamBeamoV2LogLevel.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ContextRuleFilter.h"

#include "BeamoV2LogContextRule.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoV2LogContextRule : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Enabled", Category="Beam")
	bool bEnabled = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Author", Category="Beam")
	UBeamoV2LogContextRuleAuthor* Author = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Log Level", Category="Beam")
	EBeamBeamoV2LogLevel LogLevel = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rule Filters", Category="Beam")
	TArray<UBeamoV2ContextRuleFilter*> RuleFilters = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FOptionalString Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description", Category="Beam")
	FOptionalString Description = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created At", Category="Beam")
	FOptionalInt64 CreatedAt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Updated At", Category="Beam")
	FOptionalInt64 UpdatedAt = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires At", Category="Beam")
	FOptionalInt64 ExpiresAt = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};