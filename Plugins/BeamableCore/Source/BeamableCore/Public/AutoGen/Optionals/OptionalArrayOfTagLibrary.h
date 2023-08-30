#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfTag.h"

#include "OptionalArrayOfTagLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfTagLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfTag struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Make Optional TArray<UTag*>", NativeMakeFunc))
	static FOptionalArrayOfTag MakeOptional(TArray<UTag*> Value);

	/**
	 * @brief Converts an TArray<UTag*> into an FOptionalArrayOfTag automatically.
	 * @param Value The TArray<UTag*> to convert.
	 * @return An optional with the TArray<UTag*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta = (DisplayName = "Beam - TArray<UTag*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfTag Conv_OptionalFromValue(TArray<UTag*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Optionals", meta=(DisplayName="Beam - Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfTag& Optional, TArray<UTag*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Get Optional's TArray<UTag*> Value"))
	static TArray<UTag*> GetOptionalValue(const FOptionalArrayOfTag& Optional, TArray<UTag*> DefaultValue, bool& WasSet);

	
};
