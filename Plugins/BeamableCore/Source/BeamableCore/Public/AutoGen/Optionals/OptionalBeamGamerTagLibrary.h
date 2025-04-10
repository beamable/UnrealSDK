#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamGamerTag.h"

#include "OptionalBeamGamerTagLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamGamerTagLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalBeamGamerTag struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Optionals", meta=(DisplayName="Make Optional BeamGamerTag", NativeMakeFunc))
	static FOptionalBeamGamerTag MakeOptional(FBeamGamerTag Value);

	/**
	 * @brief Converts an FBeamGamerTag into an FOptionalBeamGamerTag automatically.
	 * @param Value The FBeamGamerTag to convert.
	 * @return An optional with the BeamGamerTag set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Optionals", meta = (DisplayName="BeamGamerTag To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamGamerTag Conv_OptionalFromValue(FBeamGamerTag Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Lobby|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamGamerTag& Optional, FBeamGamerTag& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Optionals", meta=(DisplayName="Get Optional's BeamGamerTag Value"))
	static FBeamGamerTag GetOptionalValue(const FOptionalBeamGamerTag& Optional, FBeamGamerTag DefaultValue, bool& WasSet);

	
};
