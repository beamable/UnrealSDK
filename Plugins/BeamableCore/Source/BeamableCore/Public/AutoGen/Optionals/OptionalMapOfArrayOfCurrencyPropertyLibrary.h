#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfArrayOfCurrencyProperty.h"

#include "OptionalMapOfArrayOfCurrencyPropertyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMapOfArrayOfCurrencyPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalMapOfArrayOfCurrencyProperty struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Make Optional TMap<FString, FArrayOfCurrencyProperty>", NativeMakeFunc))
	static FOptionalMapOfArrayOfCurrencyProperty MakeOptional(TMap<FString, FArrayOfCurrencyProperty> Value);

	/**
	 * @brief Converts an TMap<FString, FArrayOfCurrencyProperty> into an FOptionalMapOfArrayOfCurrencyProperty automatically.
	 * @param Value The TMap<FString, FArrayOfCurrencyProperty> to convert.
	 * @return An optional with the TMap<FString, FArrayOfCurrencyProperty> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta = (DisplayName="TMap<FString, FArrayOfCurrencyProperty> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalMapOfArrayOfCurrencyProperty Conv_OptionalFromValue(TMap<FString, FArrayOfCurrencyProperty> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalMapOfArrayOfCurrencyProperty& Optional, TMap<FString, FArrayOfCurrencyProperty>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Get Optional's TMap<FString, FArrayOfCurrencyProperty> Value"))
	static TMap<FString, FArrayOfCurrencyProperty> GetOptionalValue(const FOptionalMapOfArrayOfCurrencyProperty& Optional, TMap<FString, FArrayOfCurrencyProperty> DefaultValue, bool& WasSet);

	
};
