#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfInt64.h"

#include "OptionalArrayOfInt64Library.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfInt64Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfInt64 struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Optionals", meta=(DisplayName="Make Optional TArray<int64>", NativeMakeFunc))
	static FOptionalArrayOfInt64 MakeOptional(TArray<int64> Value);

	/**
	 * @brief Converts an TArray<int64> into an FOptionalArrayOfInt64 automatically.
	 * @param Value The TArray<int64> to convert.
	 * @return An optional with the TArray<int64> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Optionals", meta = (DisplayName="TArray<int64> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfInt64 Conv_OptionalFromValue(TArray<int64> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Notification|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfInt64& Optional, TArray<int64>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Notification|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<int64> Value"))
	static TArray<int64> GetOptionalValue(const FOptionalArrayOfInt64& Optional, TArray<int64> DefaultValue, bool& WasSet);

	
};
