#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamCid.h"

#include "OptionalBeamCidLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamCidLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalBeamCid struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Make Optional BeamCid", NativeMakeFunc))
	static FOptionalBeamCid MakeOptional(FBeamCid Value);

	/**
	 * @brief Converts an FBeamCid into an FOptionalBeamCid automatically.
	 * @param Value The FBeamCid to convert.
	 * @return An optional with the BeamCid set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta = (DisplayName="BeamCid To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamCid Conv_OptionalFromValue(FBeamCid Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamCid& Optional, FBeamCid& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Get Optional's BeamCid Value"))
	static FBeamCid GetOptionalValue(const FOptionalBeamCid& Optional, FBeamCid DefaultValue, bool& WasSet);

	
};
