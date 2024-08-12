#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalOptionalJsonNodeWrapper.h"

#include "OptionalOptionalJsonNodeWrapperLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalOptionalJsonNodeWrapperLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalOptionalJsonNodeWrapper struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Make Optional OptionalJsonNodeWrapper", NativeMakeFunc))
	static FOptionalOptionalJsonNodeWrapper MakeOptional(UOptionalJsonNodeWrapper* Value);

	/**
	 * @brief Converts an UOptionalJsonNodeWrapper* into an FOptionalOptionalJsonNodeWrapper automatically.
	 * @param Value The UOptionalJsonNodeWrapper* to convert.
	 * @return An optional with the OptionalJsonNodeWrapper set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta = (DisplayName = "Beam - OptionalJsonNodeWrapper To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalOptionalJsonNodeWrapper Conv_OptionalFromValue(UOptionalJsonNodeWrapper* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Optionals", meta=(DisplayName="Beam - Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalOptionalJsonNodeWrapper& Optional, UOptionalJsonNodeWrapper*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Get Optional's OptionalJsonNodeWrapper Value"))
	static UOptionalJsonNodeWrapper* GetOptionalValue(const FOptionalOptionalJsonNodeWrapper& Optional, UOptionalJsonNodeWrapper* DefaultValue, bool& WasSet);

	
};
