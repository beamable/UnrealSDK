#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfCurrencyChangeReward.h"

#include "OptionalArrayOfCurrencyChangeRewardLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfCurrencyChangeRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfCurrencyChangeReward struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UCurrencyChangeReward*>", NativeMakeFunc))
	static FOptionalArrayOfCurrencyChangeReward MakeOptional(TArray<UCurrencyChangeReward*> Value);

	/**
	 * @brief Converts an TArray<UCurrencyChangeReward*> into an FOptionalArrayOfCurrencyChangeReward automatically.
	 * @param Value The TArray<UCurrencyChangeReward*> to convert.
	 * @return An optional with the TArray<UCurrencyChangeReward*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta = (DisplayName="TArray<UCurrencyChangeReward*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfCurrencyChangeReward Conv_OptionalFromValue(TArray<UCurrencyChangeReward*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfCurrencyChangeReward& Optional, TArray<UCurrencyChangeReward*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UCurrencyChangeReward*> Value"))
	static TArray<UCurrencyChangeReward*> GetOptionalValue(const FOptionalArrayOfCurrencyChangeReward& Optional, TArray<UCurrencyChangeReward*> DefaultValue, bool& WasSet);

	
};
