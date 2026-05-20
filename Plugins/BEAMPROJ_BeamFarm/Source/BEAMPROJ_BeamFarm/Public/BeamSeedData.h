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
 * FBeamSeedData is a shared data structure containing all seeds properties
 * used by both BeamPlantContent and BeamSeedMaterial content types.
 * 
 * This struct encapsulates all the farming gameplay data needed for:
 * - Growing crops over time
 * - Visual representation during growth stages
 * - Seed consumption and harvest yield
 */
USTRUCT(BlueprintType)
struct BEAMPROJ_BEAMFARM_API FBeamSeedData : public FBeamJsonSerializableUStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FText ContentId;
	
	// Display name shown in UI (e.g., "Wheat", "Corn")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	FText DisplayName;
	
	// Time in seconds for the crop to grow from planting to harvest
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant", meta = (ClampMin = "1.0"))
	float GrowTimeSeconds = 30.f;

	// Sprite shown on inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Plant")
	TSoftObjectPtr<UPaperSprite> SeedSprite;
	

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
			const auto SoftObjPath = SeedSprite.ToSoftObjectPath().ToString();
			Serializer->WriteValue("GrowingSprite", SoftObjPath);
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
	        SeedSprite = TSoftObjectPtr<UPaperSprite>(FSoftObjectPath(SoftObjPath));
	    }
	}

};

