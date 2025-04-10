#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamStatsType.h"

#include "OptionalBeamStatsTypeLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamStatsTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalBeamStatsType struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Optionals", meta=(DisplayName="Make Optional BeamStatsType", NativeMakeFunc))
	static FOptionalBeamStatsType MakeOptional(FBeamStatsType Value);

	/**
	 * @brief Converts an FBeamStatsType into an FOptionalBeamStatsType automatically.
	 * @param Value The FBeamStatsType to convert.
	 * @return An optional with the BeamStatsType set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Optionals", meta = (DisplayName="BeamStatsType To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamStatsType Conv_OptionalFromValue(FBeamStatsType Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Stats|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamStatsType& Optional, FBeamStatsType& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Stats|Utils|Optionals", meta=(DisplayName="Get Optional's BeamStatsType Value"))
	static FBeamStatsType GetOptionalValue(const FOptionalBeamStatsType& Optional, FBeamStatsType DefaultValue, bool& WasSet);

	
};
