#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemUpdateRequestBody.h"

#include "OptionalArrayOfItemUpdateRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfItemUpdateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfItemUpdateRequestBody struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UItemUpdateRequestBody*>", NativeMakeFunc))
	static FOptionalArrayOfItemUpdateRequestBody MakeOptional(TArray<UItemUpdateRequestBody*> Value);

	/**
	 * @brief Converts an TArray<UItemUpdateRequestBody*> into an FOptionalArrayOfItemUpdateRequestBody automatically.
	 * @param Value The TArray<UItemUpdateRequestBody*> to convert.
	 * @return An optional with the TArray<UItemUpdateRequestBody*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta = (DisplayName="TArray<UItemUpdateRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfItemUpdateRequestBody Conv_OptionalFromValue(TArray<UItemUpdateRequestBody*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfItemUpdateRequestBody& Optional, TArray<UItemUpdateRequestBody*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UItemUpdateRequestBody*> Value"))
	static TArray<UItemUpdateRequestBody*> GetOptionalValue(const FOptionalArrayOfItemUpdateRequestBody& Optional, TArray<UItemUpdateRequestBody*> DefaultValue, bool& WasSet);

	
};
