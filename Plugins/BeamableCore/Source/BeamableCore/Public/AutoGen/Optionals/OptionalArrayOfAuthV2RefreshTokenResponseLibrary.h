#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAuthV2RefreshTokenResponse.h"

#include "OptionalArrayOfAuthV2RefreshTokenResponseLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfAuthV2RefreshTokenResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfAuthV2RefreshTokenResponse struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UAuthV2RefreshTokenResponse*>", NativeMakeFunc))
	static FOptionalArrayOfAuthV2RefreshTokenResponse MakeOptional(TArray<UAuthV2RefreshTokenResponse*> Value);

	/**
	 * @brief Converts an TArray<UAuthV2RefreshTokenResponse*> into an FOptionalArrayOfAuthV2RefreshTokenResponse automatically.
	 * @param Value The TArray<UAuthV2RefreshTokenResponse*> to convert.
	 * @return An optional with the TArray<UAuthV2RefreshTokenResponse*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta = (DisplayName="TArray<UAuthV2RefreshTokenResponse*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfAuthV2RefreshTokenResponse Conv_OptionalFromValue(TArray<UAuthV2RefreshTokenResponse*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfAuthV2RefreshTokenResponse& Optional, TArray<UAuthV2RefreshTokenResponse*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UAuthV2RefreshTokenResponse*> Value"))
	static TArray<UAuthV2RefreshTokenResponse*> GetOptionalValue(const FOptionalArrayOfAuthV2RefreshTokenResponse& Optional, TArray<UAuthV2RefreshTokenResponse*> DefaultValue, bool& WasSet);

	
};
