#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalAuthV2ChallengeSolution.h"

#include "OptionalAuthV2ChallengeSolutionLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalAuthV2ChallengeSolutionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalAuthV2ChallengeSolution struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Make Optional AuthV2ChallengeSolution", NativeMakeFunc))
	static FOptionalAuthV2ChallengeSolution MakeOptional(UAuthV2ChallengeSolution* Value);

	/**
	 * @brief Converts an UAuthV2ChallengeSolution* into an FOptionalAuthV2ChallengeSolution automatically.
	 * @param Value The UAuthV2ChallengeSolution* to convert.
	 * @return An optional with the AuthV2ChallengeSolution set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta = (DisplayName="AuthV2ChallengeSolution To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalAuthV2ChallengeSolution Conv_OptionalFromValue(UAuthV2ChallengeSolution* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalAuthV2ChallengeSolution& Optional, UAuthV2ChallengeSolution*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Get Optional's AuthV2ChallengeSolution Value"))
	static UAuthV2ChallengeSolution* GetOptionalValue(const FOptionalAuthV2ChallengeSolution& Optional, UAuthV2ChallengeSolution* DefaultValue, bool& WasSet);

	
};
