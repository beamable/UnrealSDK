#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSupportedFederation.h"

#include "OptionalSupportedFederationLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalSupportedFederationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalSupportedFederation struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Make Optional SupportedFederation", NativeMakeFunc))
	static FOptionalSupportedFederation MakeOptional(USupportedFederation* Value);

	/**
	 * @brief Converts an USupportedFederation* into an FOptionalSupportedFederation automatically.
	 * @param Value The USupportedFederation* to convert.
	 * @return An optional with the SupportedFederation set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta = (DisplayName = "Beam - SupportedFederation To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalSupportedFederation Conv_OptionalFromValue(USupportedFederation* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Optionals", meta=(DisplayName="Beam - Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalSupportedFederation& Optional, USupportedFederation*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Get Optional's SupportedFederation Value"))
	static USupportedFederation* GetOptionalValue(const FOptionalSupportedFederation& Optional, USupportedFederation* DefaultValue, bool& WasSet);

	
};
