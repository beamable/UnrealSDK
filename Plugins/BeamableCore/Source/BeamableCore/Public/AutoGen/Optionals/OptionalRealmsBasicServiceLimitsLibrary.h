#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalRealmsBasicServiceLimits.h"

#include "OptionalRealmsBasicServiceLimitsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalRealmsBasicServiceLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalRealmsBasicServiceLimits struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Make Optional RealmsBasicServiceLimits", NativeMakeFunc))
	static FOptionalRealmsBasicServiceLimits MakeOptional(URealmsBasicServiceLimits* Value);

	/**
	 * @brief Converts an URealmsBasicServiceLimits* into an FOptionalRealmsBasicServiceLimits automatically.
	 * @param Value The URealmsBasicServiceLimits* to convert.
	 * @return An optional with the RealmsBasicServiceLimits set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta = (DisplayName="RealmsBasicServiceLimits To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalRealmsBasicServiceLimits Conv_OptionalFromValue(URealmsBasicServiceLimits* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalRealmsBasicServiceLimits& Optional, URealmsBasicServiceLimits*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Get Optional's RealmsBasicServiceLimits Value"))
	static URealmsBasicServiceLimits* GetOptionalValue(const FOptionalRealmsBasicServiceLimits& Optional, URealmsBasicServiceLimits* DefaultValue, bool& WasSet);

	
};
