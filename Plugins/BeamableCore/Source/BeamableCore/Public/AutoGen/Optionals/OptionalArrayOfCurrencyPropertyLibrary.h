#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCurrencyProperty.h"

#include "OptionalArrayOfCurrencyPropertyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfCurrencyPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfCurrencyProperty struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UCurrencyProperty*>", NativeMakeFunc))
	static FOptionalArrayOfCurrencyProperty MakeOptional(TArray<UCurrencyProperty*> Value);

	/**
	 * @brief Converts an TArray<UCurrencyProperty*> into an FOptionalArrayOfCurrencyProperty automatically.
	 * @param Value The TArray<UCurrencyProperty*> to convert.
	 * @return An optional with the TArray<UCurrencyProperty*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta = (DisplayName="TArray<UCurrencyProperty*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfCurrencyProperty Conv_OptionalFromValue(TArray<UCurrencyProperty*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfCurrencyProperty& Optional, TArray<UCurrencyProperty*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UCurrencyProperty*> Value"))
	static TArray<UCurrencyProperty*> GetOptionalValue(const FOptionalArrayOfCurrencyProperty& Optional, TArray<UCurrencyProperty*> DefaultValue, bool& WasSet);

	
};
