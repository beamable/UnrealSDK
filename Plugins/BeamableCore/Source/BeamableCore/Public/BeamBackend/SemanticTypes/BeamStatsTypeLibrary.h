#pragma once

#include "CoreMinimal.h"
#include "BeamGamerTag.h"
#include "BeamStatsType.h"

#include "BeamStatsTypeLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UBeamStatsTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * @brief Builds a stats type handle for the given GamerTag, Domain and with the given Visibility level.	 
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Make StatsType"))
	static FBeamStatsType MakeStatsType(TEnumAsByte<EBeamStatsDomain> Domain, TEnumAsByte<EBeamStatsVisibility> Visibility, FBeamGamerTag GamerTag)
	{
		const FString DomainAsStr = StaticEnum<EBeamStatsDomain>()->GetNameByValue(Domain).ToString().ToLower();
		const FString VisibilityAsStr = StaticEnum<EBeamStatsVisibility>()->GetNameByValue(Visibility).ToString().ToLower();
		const FString AsStr = DomainAsStr + TEXT(".") + VisibilityAsStr + TEXT(".player.") + GamerTag.AsString;
		
		return FBeamStatsType(AsStr);
	}

	/**
	 * @brief Builds a stats type handle for the given GamerTag, Domain and with the given Visibility level.	 
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Break StatsType"))
	static void BreakStatsType(const FBeamStatsType StatsType, TEnumAsByte<EBeamStatsDomain>& Domain, TEnumAsByte<EBeamStatsVisibility>& Visibility, FBeamGamerTag& GamerTag)
	{
		const auto StatType = StatsType.AsString;

		FString DomainAsStr, VisibilityAsStr, LegacyTypeAsStr, GamerTagAsStr;
		FString Remainder;

		StatType.Split(TEXT("."), &DomainAsStr, &Remainder);
		Remainder.Split(TEXT("."), &VisibilityAsStr, &Remainder);
		Remainder.Split(TEXT("."), &LegacyTypeAsStr, &Remainder);
		Remainder.Split(TEXT("."), &GamerTagAsStr, &Remainder);

		Domain = static_cast<EBeamStatsDomain>(StaticEnum<EBeamStatsDomain>()->GetValueByNameString(DomainAsStr));
		Visibility = static_cast<EBeamStatsVisibility>(StaticEnum<EBeamStatsVisibility>()->GetValueByNameString(VisibilityAsStr));
		GamerTag = FBeamGamerTag(GamerTagAsStr);
	}

	/**
	 * @brief Builds a stats type handle for the given GamerTag, Domain and with the given Visibility level.	 
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Semantic Types", meta = (DisplayName = "Beam - Copy StatsType with GamerTag"))
	static FBeamStatsType CopyStatsTypeWithGamerTag(const FBeamStatsType StatsType, const FBeamGamerTag& GamerTag)
	{
		const auto StatType = StatsType.AsString;

		// Finds the last dot in  "domain.visibility.type.gamerTag".
		int32 Idx;
		StatType.FindLastChar('.', Idx);

		// Gets the string to the left of the index after the last dot's index.
		const FString WithoutGamerTag = StatType.Left(Idx + 1);
		FString WithNewGamerTag = WithoutGamerTag + GamerTag.AsString;

		return FBeamStatsType(WithoutGamerTag);
		
	}
};
