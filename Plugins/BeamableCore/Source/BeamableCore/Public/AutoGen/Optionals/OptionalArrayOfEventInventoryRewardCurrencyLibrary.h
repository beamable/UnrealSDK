#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventInventoryRewardCurrency.h"

#include "OptionalArrayOfEventInventoryRewardCurrencyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfEventInventoryRewardCurrencyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfEventInventoryRewardCurrency struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UEventInventoryRewardCurrency*>", NativeMakeFunc))
	static FOptionalArrayOfEventInventoryRewardCurrency MakeOptional(TArray<UEventInventoryRewardCurrency*> Value);

	/**
	 * @brief Converts an TArray<UEventInventoryRewardCurrency*> into an FOptionalArrayOfEventInventoryRewardCurrency automatically.
	 * @param Value The TArray<UEventInventoryRewardCurrency*> to convert.
	 * @return An optional with the TArray<UEventInventoryRewardCurrency*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Optionals", meta = (DisplayName="TArray<UEventInventoryRewardCurrency*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfEventInventoryRewardCurrency Conv_OptionalFromValue(TArray<UEventInventoryRewardCurrency*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|EventPlayers|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfEventInventoryRewardCurrency& Optional, TArray<UEventInventoryRewardCurrency*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UEventInventoryRewardCurrency*> Value"))
	static TArray<UEventInventoryRewardCurrency*> GetOptionalValue(const FOptionalArrayOfEventInventoryRewardCurrency& Optional, TArray<UEventInventoryRewardCurrency*> DefaultValue, bool& WasSet);

	
};
