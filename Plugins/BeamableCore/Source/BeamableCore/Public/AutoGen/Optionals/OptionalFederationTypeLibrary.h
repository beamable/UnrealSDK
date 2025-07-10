#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalFederationType.h"

#include "OptionalFederationTypeLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalFederationTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalFederationType struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional BeamFederationType", NativeMakeFunc))
	static FOptionalFederationType MakeOptional(EBeamFederationType Value);

	/**
	 * @brief Converts an EBeamFederationType into an FOptionalFederationType automatically.
	 * @param Value The EBeamFederationType to convert.
	 * @return An optional with the BeamFederationType set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="BeamFederationType To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalFederationType Conv_OptionalFromValue(EBeamFederationType Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalFederationType& Optional, EBeamFederationType& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's BeamFederationType Value"))
	static EBeamFederationType GetOptionalValue(const FOptionalFederationType& Optional, EBeamFederationType DefaultValue, bool& WasSet);

	
};
