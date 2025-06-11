#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalGatewayLimits.h"

#include "OptionalGatewayLimitsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalGatewayLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalGatewayLimits struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Make Optional GatewayLimits", NativeMakeFunc))
	static FOptionalGatewayLimits MakeOptional(UGatewayLimits* Value);

	/**
	 * @brief Converts an UGatewayLimits* into an FOptionalGatewayLimits automatically.
	 * @param Value The UGatewayLimits* to convert.
	 * @return An optional with the GatewayLimits set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta = (DisplayName="GatewayLimits To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalGatewayLimits Conv_OptionalFromValue(UGatewayLimits* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalGatewayLimits& Optional, UGatewayLimits*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Get Optional's GatewayLimits Value"))
	static UGatewayLimits* GetOptionalValue(const FOptionalGatewayLimits& Optional, UGatewayLimits* DefaultValue, bool& WasSet);

	
};
