#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPeriod.h"

#include "OptionalPeriodLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalPeriodLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalPeriod struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Optionals", meta=(DisplayName="Make Optional Period", NativeMakeFunc))
	static FOptionalPeriod MakeOptional(UPeriod* Value);

	/**
	 * @brief Converts an UPeriod* into an FOptionalPeriod automatically.
	 * @param Value The UPeriod* to convert.
	 * @return An optional with the Period set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Optionals", meta = (DisplayName="Period To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalPeriod Conv_OptionalFromValue(UPeriod* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Commerce|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalPeriod& Optional, UPeriod*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Optionals", meta=(DisplayName="Get Optional's Period Value"))
	static UPeriod* GetOptionalValue(const FOptionalPeriod& Optional, UPeriod* DefaultValue, bool& WasSet);

	
};
