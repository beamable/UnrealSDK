#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfInFlightMessage.h"

#include "OptionalArrayOfInFlightMessageLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfInFlightMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfInFlightMessage struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UInFlightMessage*>", NativeMakeFunc))
	static FOptionalArrayOfInFlightMessage MakeOptional(TArray<UInFlightMessage*> Value);

	/**
	 * @brief Converts an TArray<UInFlightMessage*> into an FOptionalArrayOfInFlightMessage automatically.
	 * @param Value The TArray<UInFlightMessage*> to convert.
	 * @return An optional with the TArray<UInFlightMessage*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Optionals", meta = (DisplayName="TArray<UInFlightMessage*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfInFlightMessage Conv_OptionalFromValue(TArray<UInFlightMessage*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Events|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfInFlightMessage& Optional, TArray<UInFlightMessage*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Events|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UInFlightMessage*> Value"))
	static TArray<UInFlightMessage*> GetOptionalValue(const FOptionalArrayOfInFlightMessage& Optional, TArray<UInFlightMessage*> DefaultValue, bool& WasSet);

	
};
