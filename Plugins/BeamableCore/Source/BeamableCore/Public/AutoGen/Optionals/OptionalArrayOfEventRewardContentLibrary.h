#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfEventRewardContent.h"

#include "OptionalArrayOfEventRewardContentLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfEventRewardContentLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfEventRewardContent struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UEventRewardContent*>", NativeMakeFunc))
	static FOptionalArrayOfEventRewardContent MakeOptional(TArray<UEventRewardContent*> Value);

	/**
	 * @brief Converts an TArray<UEventRewardContent*> into an FOptionalArrayOfEventRewardContent automatically.
	 * @param Value The TArray<UEventRewardContent*> to convert.
	 * @return An optional with the TArray<UEventRewardContent*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Optionals", meta = (DisplayName="TArray<UEventRewardContent*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfEventRewardContent Conv_OptionalFromValue(TArray<UEventRewardContent*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Events|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfEventRewardContent& Optional, TArray<UEventRewardContent*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UEventRewardContent*> Value"))
	static TArray<UEventRewardContent*> GetOptionalValue(const FOptionalArrayOfEventRewardContent& Optional, TArray<UEventRewardContent*> DefaultValue, bool& WasSet);

	
};
