#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalTokenResponse.h"

#include "OptionalTokenResponseLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalTokenResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalTokenResponse struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Optionals", meta=(DisplayName="Make Optional TokenResponse", NativeMakeFunc))
	static FOptionalTokenResponse MakeOptional(UTokenResponse* Value);

	/**
	 * @brief Converts an UTokenResponse* into an FOptionalTokenResponse automatically.
	 * @param Value The UTokenResponse* to convert.
	 * @return An optional with the TokenResponse set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Optionals", meta = (DisplayName="TokenResponse To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalTokenResponse Conv_OptionalFromValue(UTokenResponse* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Accounts|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalTokenResponse& Optional, UTokenResponse*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Optionals", meta=(DisplayName="Get Optional's TokenResponse Value"))
	static UTokenResponse* GetOptionalValue(const FOptionalTokenResponse& Optional, UTokenResponse* DefaultValue, bool& WasSet);

	
};
