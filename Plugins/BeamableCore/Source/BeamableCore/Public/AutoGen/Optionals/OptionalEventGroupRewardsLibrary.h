#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventGroupRewards.h"

#include "OptionalEventGroupRewardsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalEventGroupRewardsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalEventGroupRewards struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Optionals", meta=(DisplayName="Make Optional EventGroupRewards", NativeMakeFunc))
	static FOptionalEventGroupRewards MakeOptional(UEventGroupRewards* Value);

	/**
	 * @brief Converts an UEventGroupRewards* into an FOptionalEventGroupRewards automatically.
	 * @param Value The UEventGroupRewards* to convert.
	 * @return An optional with the EventGroupRewards set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Optionals", meta = (DisplayName="EventGroupRewards To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalEventGroupRewards Conv_OptionalFromValue(UEventGroupRewards* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Events|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalEventGroupRewards& Optional, UEventGroupRewards*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Optionals", meta=(DisplayName="Get Optional's EventGroupRewards Value"))
	static UEventGroupRewards* GetOptionalValue(const FOptionalEventGroupRewards& Optional, UEventGroupRewards* DefaultValue, bool& WasSet);

	
};
