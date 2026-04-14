#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"
#include "Serialization/BeamJsonUtils.h"

#include "PredicateDTO.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UPredicateDTO : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Kind", Category="Beam")
	FString Kind = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="As", Category="Beam")
	FOptionalString As = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Case Insensitive", Category="Beam")
	FOptionalBool bCaseInsensitive = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Include Lower", Category="Beam")
	FOptionalBool bIncludeLower = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Include Upper", Category="Beam")
	FOptionalBool bIncludeUpper = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Lower", Category="Beam")
	FOptionalString Lower = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Upper", Category="Beam")
	FOptionalString Upper = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Substr", Category="Beam")
	FOptionalString Substr = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category="Beam")
	FOptionalString Value = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Values", Category="Beam")
	FOptionalArrayOfString Values = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};