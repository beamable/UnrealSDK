#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2OrderDirection.h"

#include "OptionalBeamoV2OrderDirectionLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamoV2OrderDirectionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalBeamoV2OrderDirection struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional BeamBeamoV2OrderDirection", NativeMakeFunc))
	static FOptionalBeamoV2OrderDirection MakeOptional(EBeamBeamoV2OrderDirection Value);

	/**
	 * @brief Converts an EBeamBeamoV2OrderDirection into an FOptionalBeamoV2OrderDirection automatically.
	 * @param Value The EBeamBeamoV2OrderDirection to convert.
	 * @return An optional with the BeamBeamoV2OrderDirection set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="BeamBeamoV2OrderDirection To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamoV2OrderDirection Conv_OptionalFromValue(EBeamBeamoV2OrderDirection Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamoV2OrderDirection& Optional, EBeamBeamoV2OrderDirection& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's BeamBeamoV2OrderDirection Value"))
	static EBeamBeamoV2OrderDirection GetOptionalValue(const FOptionalBeamoV2OrderDirection& Optional, EBeamBeamoV2OrderDirection DefaultValue, bool& WasSet);

	
};
