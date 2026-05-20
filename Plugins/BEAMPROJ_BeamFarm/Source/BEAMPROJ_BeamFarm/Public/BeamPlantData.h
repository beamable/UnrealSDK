// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Internationalization/TextNamespaceUtil.h"
#include "Serialization/BeamJsonUtils.h"
#include "UObject/SoftObjectPath.h"
#include "BeamPlantData.generated.h"

UENUM(BlueprintType)
enum EBeamFarmItemType
{
	Seed UMETA(DisplayName = "Seed"),
	MutatedPlant UMETA(DisplayName = "Mutated Plant"),
};

UENUM(BlueprintType, Blueprintable)
enum EBeamFarmPropertyType
{
	Corrosive UMETA(DisplayName = "Corrosive"),
	Mutagenic UMETA(DisplayName = "Mutagenic"),
	Radioactive UMETA(DisplayName = "Radioactive"),
};


/**
 * FBeamPlantData represents a harvested crop item from UBeamPlantContent.
 * It holds the harvest-ready visual and display info for the farm slot and inventory.
 * Grow time and growing visual live on FBeamSeedData instead.
 */
USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamPlantData : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FText ContentId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FText Id;

	// Display name shown in UI (e.g., "Wheat", "Corn")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FText DisplayName;

	// Sprite shown on the farm slot when the crop is ready to harvest
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	TSoftObjectPtr<UPaperSprite> ReadyToHarvestSprite;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		{
			FString ToSerialize;
			if (DisplayName.IsFromStringTable())
			{
				FName TableId;
				FString Key;
				FTextInspector::GetTableIdAndKey(DisplayName, TableId, Key);
				ToSerialize = TEXT("BEAM_ST₢") + TableId.ToString() + TEXT("₢") + Key;
			}
			else
			{
				ToSerialize = DisplayName.ToString();
			}
			Serializer->WriteValue("DisplayName", ToSerialize);
		}

		{
			const auto SoftObjPath = ReadyToHarvestSprite.ToSoftObjectPath().ToString();
			Serializer->WriteValue("ReadyToHarvestSprite", SoftObjPath);
		}
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
		{
			FString SerializedVal;
			UBeamJsonUtils::DeserializeRawPrimitive<FString>(TEXT("DisplayName"), Bag, SerializedVal);
			if (SerializedVal.StartsWith(TEXT("BEAM_ST₢")))
			{
				FString TableIdStr, KeyStr;
				SerializedVal.Split(TEXT("₢"), &TableIdStr, &KeyStr);
				TableIdStr.RemoveFromStart(TEXT("BEAM_ST₢"));
				KeyStr.Split(TEXT("₢"), &TableIdStr, &KeyStr);
				DisplayName = FText::FromStringTable(*TableIdStr, KeyStr);
			}
			else
			{
				DisplayName = FText::FromString(SerializedVal);
			}
		}

		{
			FString SoftObjPath;
			UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ReadyToHarvestSprite"), Bag, SoftObjPath);
			ReadyToHarvestSprite = TSoftObjectPtr<UPaperSprite>(FSoftObjectPath(SoftObjPath));
		}
	}

};
