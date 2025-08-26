#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2FederationType.h"

#include "OptionalBeamoV2FederationTypeLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamoV2FederationTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalBeamoV2FederationType struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional BeamBeamoV2FederationType", NativeMakeFunc))
	static FOptionalBeamoV2FederationType MakeOptional(EBeamBeamoV2FederationType Value);

	/**
	 * @brief Converts an EBeamBeamoV2FederationType into an FOptionalBeamoV2FederationType automatically.
	 * @param Value The EBeamBeamoV2FederationType to convert.
	 * @return An optional with the BeamBeamoV2FederationType set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="BeamBeamoV2FederationType To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamoV2FederationType Conv_OptionalFromValue(EBeamBeamoV2FederationType Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamoV2FederationType& Optional, EBeamBeamoV2FederationType& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's BeamBeamoV2FederationType Value"))
	static EBeamBeamoV2FederationType GetOptionalValue(const FOptionalBeamoV2FederationType& Optional, EBeamBeamoV2FederationType DefaultValue, bool& WasSet);

	
};
