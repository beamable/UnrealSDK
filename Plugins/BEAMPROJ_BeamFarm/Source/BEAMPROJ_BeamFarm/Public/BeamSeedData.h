// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Internationalization/TextNamespaceUtil.h"
#include "Serialization/BeamJsonUtils.h"
#include "UObject/SoftObjectPath.h"
#include "BeamSeedData.generated.h"


/**
 * FBeamSeedData contains all data for a seed item:
 * - How it looks in inventory (SeedSprite)
 * - How it looks and how long it grows on a farm slot (GrowingSprite, GrowTimeSeconds)
 * - Which BeamPlantContent item the player receives on harvest (HarvestItemContentId)
 */
USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamSeedData : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	// Display name shown in UI (e.g., "Wheat Seed", "Corn Seed")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Seed")
	FText DisplayName;

	// Time in seconds for the seed to grow from planting to harvest
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Seed", meta = (ClampMin = "1.0"))
	float GrowTimeSeconds = 30.f;

	// Sprite shown in the player's inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Seed")
	TSoftObjectPtr<UPaperSprite> SeedSprite;

	// Sprite shown on the farm slot while the seed is growing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Seed")
	TSoftObjectPtr<UPaperSprite> GrowingSprite;

	// Content ID of the UBeamPlantContent item the player receives when harvesting
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Seed")
	FBeamContentId HarvestItemContentId;

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

		Serializer->WriteValue("GrowTimeSeconds", GrowTimeSeconds);

		{
			const auto SoftObjPath = SeedSprite.ToSoftObjectPath().ToString();
			Serializer->WriteValue("SeedSprite", SoftObjPath);
		}

		{
			const auto SoftObjPath = GrowingSprite.ToSoftObjectPath().ToString();
			Serializer->WriteValue("GrowingSprite", SoftObjPath);
		}

		Serializer->WriteValue("HarvestItemContentId", HarvestItemContentId.AsString);
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
			double TempValue = 0.0;
			UBeamJsonUtils::DeserializeRawPrimitive(TEXT("GrowTimeSeconds"), Bag, TempValue);
			GrowTimeSeconds = static_cast<float>(TempValue);
		}

		{
			FString SoftObjPath;
			UBeamJsonUtils::DeserializeRawPrimitive(TEXT("SeedSprite"), Bag, SoftObjPath);
			SeedSprite = TSoftObjectPtr<UPaperSprite>(FSoftObjectPath(SoftObjPath));
		}

		{
			FString SoftObjPath;
			UBeamJsonUtils::DeserializeRawPrimitive(TEXT("GrowingSprite"), Bag, SoftObjPath);
			GrowingSprite = TSoftObjectPtr<UPaperSprite>(FSoftObjectPath(SoftObjPath));
		}
		FString HarvestItemContentIdStr;
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("HarvestItemContentId"), Bag, HarvestItemContentIdStr);
		HarvestItemContentId = FBeamContentId(HarvestItemContentIdStr);
	}
};
