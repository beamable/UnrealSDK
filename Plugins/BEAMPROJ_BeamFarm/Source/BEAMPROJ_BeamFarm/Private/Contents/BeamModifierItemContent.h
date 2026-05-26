// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Content/BeamContentTypes/BeamCurrencyContent.h"
#include "BeamModifierItemData.h"
#include "PaperSprite.h"

#include "BeamModifierItemContent.generated.h"

/**
 * UBeamModifierItemContent represents a plant modifier item in the Beamable content system.
 * Content type ID: "plant_modifier"
 *
 * Modifier items are Beamable currencies — players accumulate them and spend one unit
 * per application in the mutation lab (via the MutateWithModifiers microservice call).
 *
 * Each modifier defines one or more FBeamPropertyModifierDelta entries. When applied,
 * the server adds each Delta to the corresponding property of the target plant item,
 * clamping the result to [0, 10].
 *
 * To create modifier content:
 *   1. In Unreal Editor, use the Beamable Content browser to create new "plant_modifier" entries.
 *   2. Set PropertyModifiers with the desired property names and delta values.
 *   3. Publish the content to your realm.
 *
 * Example content IDs:
 *   plant_modifier.corrosive_boost      — grants +3 Corrosive
 *   plant_modifier.mutagenic_inhibitor  — grants -2 Mutagenic
 *   plant_modifier.radioactive_surge    — grants +5 Radioactive
 */
UCLASS(BlueprintType)
class BEAMPROJ_BEAMFARM_API UBeamModifierItemContent : public UBeamCurrencyContent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void GetContentType_UBeamModifierItemContent(FString& Result) { Result = TEXT("plant_modifier"); }

	// Icon shown in inventory and mutation lab UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Modifier")
	TSoftObjectPtr<UPaperSprite> ItemIcon;

	// Display name shown in inventory and mutation lab (e.g. "Corrosive Boost", "Mutagenic Inhibitor")
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Modifier")
	FText DisplayName;

	// Description shown in the mutation lab UI when inspecting this modifier item
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Modifier")
	FText Description;

	// Property changes this modifier applies when used in the mutation lab
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BeamFarm|Modifier")
	TArray<FBeamPropertyModifierDelta> PropertyModifiers;
};
