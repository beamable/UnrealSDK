#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "BeamBackend/SemanticTypes/BeamPid.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "Project.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UProject : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived", Category="Beam")
	bool bArchived = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Root", Category="Beam")
	bool bRoot = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Secret", Category="Beam")
	FString Secret = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name", Category="Beam")
	FBeamPid Name = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Plan", Category="Beam")
	FString Plan = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Custom Charts", Category="Beam")
	TMap<FString, FString> CustomCharts = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sharded", Category="Beam")
	FOptionalBool bSharded = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Sigval", Category="Beam")
	FOptionalBool bSigval = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Display Name", Category="Beam")
	FOptionalString DisplayName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Parent", Category="Beam")
	FOptionalString Parent = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Status", Category="Beam")
	FOptionalString Status = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	FOptionalInt64 Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Children", Category="Beam")
	FOptionalArrayOfString Children = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Config", Category="Beam")
	FOptionalMapOfString Config = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};