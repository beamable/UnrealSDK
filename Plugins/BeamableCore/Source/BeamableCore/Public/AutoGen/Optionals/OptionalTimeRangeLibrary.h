#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalTimeRange.h"

#include "OptionalTimeRangeLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalTimeRangeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalTimeRange struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Make Optional TimeRange", NativeMakeFunc))
	static FOptionalTimeRange MakeOptional(UTimeRange* Value);

	/**
	 * @brief Converts an UTimeRange* into an FOptionalTimeRange automatically.
	 * @param Value The UTimeRange* to convert.
	 * @return An optional with the TimeRange set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta = (DisplayName="TimeRange To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalTimeRange Conv_OptionalFromValue(UTimeRange* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalTimeRange& Optional, UTimeRange*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Get Optional's TimeRange Value"))
	static UTimeRange* GetOptionalValue(const FOptionalTimeRange& Optional, UTimeRange* DefaultValue, bool& WasSet);

	
};
