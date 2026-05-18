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
	RawPlant UMETA(DisplayName = "Raw Plant"),
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
 * FBeamPlantData is a shared data structure containing all plant/crop properties
 * used by both BeamPlantContent and BeamPlantRawMaterial content types.
 * 
 * This struct encapsulates all the farming gameplay data needed for:
 * - Growing crops over time
 * - Visual representation during growth stages
 * - Seed consumption and harvest yield
 */
USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamPlantData : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	// Unique identifier for the plant type (e.g., "Wheat", "Corn")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FString Id;
	
	// Display name shown in UI (e.g., "Wheat", "Corn")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FText DisplayName;
	
	// Time in seconds for the crop to grow from planting to harvest
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant", meta = (ClampMin = "1.0"))
	float GrowTimeSeconds = 30.f;

	// Sprite shown on the farm slot while the crop is growing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	TSoftObjectPtr<UPaperSprite> GrowingSprite;

	// Sprite shown on the farm slot when the crop is ready to harvest
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	TSoftObjectPtr<UPaperSprite> ReadyToHarvestSprite;
	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override
	{
		// Serialize FText DisplayName
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

		// Serialize float GrowTimeSeconds
		Serializer->WriteValue("GrowTimeSeconds", GrowTimeSeconds);

		// Serialize TSoftObjectPtr<UPaperSprite> GrowingSprite
		{
			const auto SoftObjPath = GrowingSprite.ToSoftObjectPath().ToString();
			Serializer->WriteValue("GrowingSprite", SoftObjPath);
		}

		// Serialize TSoftObjectPtr<UPaperSprite> ReadyToHarvestSprite
		{
			const auto SoftObjPath = ReadyToHarvestSprite.ToSoftObjectPath().ToString();
			Serializer->WriteValue("ReadyToHarvestSprite", SoftObjPath);
		}
		
	}

	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override
	{
	    // Deserialize FText DisplayName
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

	    // Deserialize float GrowTimeSeconds
	    {
	        double TempValue = 0.0;
	    	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("GrowTimeSeconds"), Bag, TempValue);
	        GrowTimeSeconds = static_cast<float>(TempValue);
	    }

	    // Deserialize TSoftObjectPtr<UPaperSprite> GrowingSprite
	    {
	        FString SoftObjPath;
	    	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("GrowingSprite"), Bag, SoftObjPath);
	        GrowingSprite = TSoftObjectPtr<UPaperSprite>(FSoftObjectPath(SoftObjPath));
	    }

	    // Deserialize TSoftObjectPtr<UPaperSprite> ReadyToHarvestSprite
	    {
	        FString SoftObjPath;
	    	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("ReadyToHarvestSprite"), Bag, SoftObjPath);
	        ReadyToHarvestSprite = TSoftObjectPtr<UPaperSprite>(FSoftObjectPath(SoftObjPath));
	    }
	}

};

