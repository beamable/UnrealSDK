#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfDonationRequestBody.h"

#include "OptionalMapOfDonationRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMapOfDonationRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalMapOfDonationRequestBody struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Make Optional TMap<FString, UDonationRequestBody*>", NativeMakeFunc))
	static FOptionalMapOfDonationRequestBody MakeOptional(TMap<FString, UDonationRequestBody*> Value);

	/**
	 * @brief Converts an TMap<FString, UDonationRequestBody*> into an FOptionalMapOfDonationRequestBody automatically.
	 * @param Value The TMap<FString, UDonationRequestBody*> to convert.
	 * @return An optional with the TMap<FString, UDonationRequestBody*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta = (DisplayName="TMap<FString, UDonationRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalMapOfDonationRequestBody Conv_OptionalFromValue(TMap<FString, UDonationRequestBody*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalMapOfDonationRequestBody& Optional, TMap<FString, UDonationRequestBody*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Get Optional's TMap<FString, UDonationRequestBody*> Value"))
	static TMap<FString, UDonationRequestBody*> GetOptionalValue(const FOptionalMapOfDonationRequestBody& Optional, TMap<FString, UDonationRequestBody*> DefaultValue, bool& WasSet);

	
};
