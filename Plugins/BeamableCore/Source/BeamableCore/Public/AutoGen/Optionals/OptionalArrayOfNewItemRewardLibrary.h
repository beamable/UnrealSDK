#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfNewItemReward.h"

#include "OptionalArrayOfNewItemRewardLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfNewItemRewardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfNewItemReward struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UNewItemReward*>", NativeMakeFunc))
	static FOptionalArrayOfNewItemReward MakeOptional(TArray<UNewItemReward*> Value);

	/**
	 * @brief Converts an TArray<UNewItemReward*> into an FOptionalArrayOfNewItemReward automatically.
	 * @param Value The TArray<UNewItemReward*> to convert.
	 * @return An optional with the TArray<UNewItemReward*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta = (DisplayName="TArray<UNewItemReward*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfNewItemReward Conv_OptionalFromValue(TArray<UNewItemReward*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfNewItemReward& Optional, TArray<UNewItemReward*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UNewItemReward*> Value"))
	static TArray<UNewItemReward*> GetOptionalValue(const FOptionalArrayOfNewItemReward& Optional, TArray<UNewItemReward*> DefaultValue, bool& WasSet);

	
};
