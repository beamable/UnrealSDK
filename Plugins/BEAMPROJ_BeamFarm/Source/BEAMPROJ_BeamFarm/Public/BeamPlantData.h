// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSprite.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Internationalization/TextNamespaceUtil.h"
#include "Serialization/BeamJsonUtils.h"
#include "UObject/SoftObjectPath.h"
#include "BeamPlantData.generated.h"

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

	// Display name shown in UI (e.g., "Wheat", "Corn")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FText DisplayName;

	// Icon for inventory/UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	TSoftObjectPtr<UTexture2D> Icon;

	// Time in seconds for the crop to grow from planting to harvest
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant", meta = (ClampMin = "1.0"))
	float GrowTimeSeconds = 30.f;

	// Sprite shown on the farm slot while the crop is growing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	TSoftObjectPtr<UPaperSprite> GrowingSprite;

	// Sprite shown on the farm slot when the crop is ready to harvest
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	TSoftObjectPtr<UPaperSprite> ReadyToHarvestSprite;

	// Beamable content ID of the seed item consumed from inventory when planting
	// Example: "items.wheat_seed"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FString SeedItemContentId;

	// Beamable content ID of the item added to inventory on harvest
	// Example: "items.wheat"
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FString HarvestItemContentId;

	// Number of items to add to inventory when harvested
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant", meta = (ClampMin = "1"))
	int32 HarvestYield = 1;

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

		// Serialize TSoftObjectPtr<UTexture2D> Icon
		{
			const auto SoftObjPath = Icon.ToSoftObjectPath().ToString();
			Serializer->WriteValue("Icon", SoftObjPath);
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

		// Serialize FString SeedItemContentId
		Serializer->WriteValue("SeedItemContentId", SeedItemContentId);

		// Serialize FString HarvestItemContentId
		Serializer->WriteValue("HarvestItemContentId", HarvestItemContentId);

		// Serialize int32 HarvestYield
		Serializer->WriteValue("HarvestYield", HarvestYield);
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

	    // Deserialize TSoftObjectPtr<UTexture2D> Icon
	    {
	        FString SoftObjPath;
	        Bag->TryGetStringField(TEXT("Icon"), SoftObjPath);
	        Icon = TSoftObjectPtr<UTexture2D>(FSoftObjectPath(SoftObjPath));
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

	    // Deserialize FString SeedItemContentId
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("SeedItemContentId"), Bag, SeedItemContentId);
	      
	    // Deserialize FString HarvestItemContentId
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("HarvestItemContentId"), Bag, HarvestItemContentId);
	    
	    // Deserialize int32 HarvestYield
		UBeamJsonUtils::DeserializeRawPrimitive(TEXT("HarvestYield"), Bag, HarvestYield);
	}

};
