#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamGamerTag.h"

#include "OptionalArrayOfBeamGamerTagLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfBeamGamerTagLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfBeamGamerTag struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Optionals", meta=(DisplayName="Make Optional TArray<FBeamGamerTag>", NativeMakeFunc))
	static FOptionalArrayOfBeamGamerTag MakeOptional(TArray<FBeamGamerTag> Value);

	/**
	 * @brief Converts an TArray<FBeamGamerTag> into an FOptionalArrayOfBeamGamerTag automatically.
	 * @param Value The TArray<FBeamGamerTag> to convert.
	 * @return An optional with the TArray<FBeamGamerTag> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Optionals", meta = (DisplayName="TArray<FBeamGamerTag> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfBeamGamerTag Conv_OptionalFromValue(TArray<FBeamGamerTag> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Party|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfBeamGamerTag& Optional, TArray<FBeamGamerTag>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<FBeamGamerTag> Value"))
	static TArray<FBeamGamerTag> GetOptionalValue(const FOptionalArrayOfBeamGamerTag& Optional, TArray<FBeamGamerTag> DefaultValue, bool& WasSet);

	
};
