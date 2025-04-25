#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfInt32.h"

#include "OptionalArrayOfInt32Library.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfInt32Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfInt32 struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Optionals", meta=(DisplayName="Make Optional TArray<int32>", NativeMakeFunc))
	static FOptionalArrayOfInt32 MakeOptional(TArray<int32> Value);

	/**
	 * @brief Converts an TArray<int32> into an FOptionalArrayOfInt32 automatically.
	 * @param Value The TArray<int32> to convert.
	 * @return An optional with the TArray<int32> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Optionals", meta = (DisplayName="TArray<int32> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfInt32 Conv_OptionalFromValue(TArray<int32> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Commerce|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfInt32& Optional, TArray<int32>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<int32> Value"))
	static TArray<int32> GetOptionalValue(const FOptionalArrayOfInt32& Optional, TArray<int32> DefaultValue, bool& WasSet);

	
};
