#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"

#include "OptionalMapOfStringLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMapOfStringLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalMapOfString struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Make Optional TMap<FString, FString>", NativeMakeFunc))
	static FOptionalMapOfString MakeOptional(TMap<FString, FString> Value);

	/**
	 * @brief Converts an TMap<FString, FString> into an FOptionalMapOfString automatically.
	 * @param Value The TMap<FString, FString> to convert.
	 * @return An optional with the TMap<FString, FString> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta = (DisplayName="TMap<FString, FString> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalMapOfString Conv_OptionalFromValue(TMap<FString, FString> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalMapOfString& Optional, TMap<FString, FString>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Get Optional's TMap<FString, FString> Value"))
	static TMap<FString, FString> GetOptionalValue(const FOptionalMapOfString& Optional, TMap<FString, FString> DefaultValue, bool& WasSet);

	
};
