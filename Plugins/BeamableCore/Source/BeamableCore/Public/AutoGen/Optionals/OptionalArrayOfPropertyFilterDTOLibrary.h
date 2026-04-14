#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPropertyFilterDTO.h"

#include "OptionalArrayOfPropertyFilterDTOLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfPropertyFilterDTOLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfPropertyFilterDTO struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UPropertyFilterDTO*>", NativeMakeFunc))
	static FOptionalArrayOfPropertyFilterDTO MakeOptional(TArray<UPropertyFilterDTO*> Value);

	/**
	 * @brief Converts an TArray<UPropertyFilterDTO*> into an FOptionalArrayOfPropertyFilterDTO automatically.
	 * @param Value The TArray<UPropertyFilterDTO*> to convert.
	 * @return An optional with the TArray<UPropertyFilterDTO*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta = (DisplayName="TArray<UPropertyFilterDTO*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfPropertyFilterDTO Conv_OptionalFromValue(TArray<UPropertyFilterDTO*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfPropertyFilterDTO& Optional, TArray<UPropertyFilterDTO*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UPropertyFilterDTO*> Value"))
	static TArray<UPropertyFilterDTO*> GetOptionalValue(const FOptionalArrayOfPropertyFilterDTO& Optional, TArray<UPropertyFilterDTO*> DefaultValue, bool& WasSet);

	
};
