#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"

#include "OptionalInt32Library.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalInt32Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalInt32 struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Shared|Utils|Optionals", meta=(DisplayName="Make Optional Int32", NativeMakeFunc))
	static FOptionalInt32 MakeOptional(int32 Value);

	/**
	 * @brief Converts an int32 into an FOptionalInt32 automatically.
	 * @param Value The int32 to convert.
	 * @return An optional with the Int32 set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Shared|Utils|Optionals", meta = (DisplayName="Int32 To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalInt32 Conv_OptionalFromValue(int32 Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Shared|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalInt32& Optional, int32& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Shared|Utils|Optionals", meta=(DisplayName="Get Optional's Int32 Value"))
	static int32 GetOptionalValue(const FOptionalInt32& Optional, int32 DefaultValue, bool& WasSet);

	
};
