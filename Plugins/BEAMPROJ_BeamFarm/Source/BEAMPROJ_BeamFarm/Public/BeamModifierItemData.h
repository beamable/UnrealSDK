// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamModifierItemData.generated.h"

/**
 * FBeamPropertyModifierDelta defines a single property change applied by a modifier item
 * in the mutation lab. PropertyName must match one of the EBeamFarmPropertyType enum names
 * ("Corrosive", "Mutagenic", "Radioactive"). Delta is signed — positive increases the
 * property value, negative decreases it. The server clamps the result to [0, 10].
 */
USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamPropertyModifierDelta : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	// Property name to modify — must match EBeamFarmPropertyType names
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Modifier")
	FString PropertyName;

	// Signed change to apply: positive = increase, negative = decrease
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Modifier")
	int32 Delta = 0;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		Serializer->WriteValue(TEXT("PropertyName"), PropertyName);
		Serializer->WriteValue(TEXT("Delta"), Delta);
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("PropertyName"), Bag, PropertyName);
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("Delta"), Bag, Delta);
	}
};
