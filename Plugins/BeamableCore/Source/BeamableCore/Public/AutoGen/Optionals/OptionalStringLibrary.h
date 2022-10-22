#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "OptionalStringLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalStringLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	* @brief Constructs an FOptionalInt struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Make")
	static FOptionalString MakeOptionalString(FString Value);

	/**
	 * @brief Converts an FString into an FOptionalString automatically.
	 * @param Value The string to convert
	 * @return An optional with the string set as it's value.
	 */
	UFUNCTION(BlueprintPure, meta = (DisplayName = "String To Optional", CompactNodeTitle = "->", BlueprintAutocast), Category="Beam|Converter")
	static FOptionalString Conv_OptionalStringFromValue(FString Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.  
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam")
	static FString GetValueWithFallback(const FOptionalString& Optional, const FString& DefaultValue, bool& WasSet);

	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, meta = (ExpandBoolAsExecs="ReturnValue"), Category="Beam")
	static bool HasValue(const FOptionalString& Optional, FString& Value);
};
