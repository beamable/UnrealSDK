#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfDouble.h"

#include "OptionalMapOfDoubleLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMapOfDoubleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalMapOfDouble struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|PlayerTicket|Utils|Optionals", meta=(DisplayName="Make Optional TMap<FString, double>", NativeMakeFunc))
	static FOptionalMapOfDouble MakeOptional(TMap<FString, double> Value);

	/**
	 * @brief Converts an TMap<FString, double> into an FOptionalMapOfDouble automatically.
	 * @param Value The TMap<FString, double> to convert.
	 * @return An optional with the TMap<FString, double> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|PlayerTicket|Utils|Optionals", meta = (DisplayName="TMap<FString, double> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalMapOfDouble Conv_OptionalFromValue(TMap<FString, double> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|PlayerTicket|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalMapOfDouble& Optional, TMap<FString, double>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|PlayerTicket|Utils|Optionals", meta=(DisplayName="Get Optional's TMap<FString, double> Value"))
	static TMap<FString, double> GetOptionalValue(const FOptionalMapOfDouble& Optional, TMap<FString, double> DefaultValue, bool& WasSet);

	
};
