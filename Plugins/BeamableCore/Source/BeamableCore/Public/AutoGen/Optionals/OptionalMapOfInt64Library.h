#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfInt64.h"

#include "OptionalMapOfInt64Library.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMapOfInt64Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalMapOfInt64 struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Make Optional TMap<FString, int64>", NativeMakeFunc))
	static FOptionalMapOfInt64 MakeOptional(TMap<FString, int64> Value);

	/**
	 * @brief Converts an TMap<FString, int64> into an FOptionalMapOfInt64 automatically.
	 * @param Value The TMap<FString, int64> to convert.
	 * @return An optional with the TMap<FString, int64> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta = (DisplayName="TMap<FString, int64> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalMapOfInt64 Conv_OptionalFromValue(TMap<FString, int64> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalMapOfInt64& Optional, TMap<FString, int64>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Get Optional's TMap<FString, int64> Value"))
	static TMap<FString, int64> GetOptionalValue(const FOptionalMapOfInt64& Optional, TMap<FString, int64> DefaultValue, bool& WasSet);

	
};
