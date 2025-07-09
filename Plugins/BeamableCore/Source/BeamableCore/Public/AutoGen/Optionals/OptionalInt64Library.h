#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "OptionalInt64Library.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalInt64Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalInt64 struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional Int64", NativeMakeFunc))
	static FOptionalInt64 MakeOptional(int64 Value);

	/**
	 * @brief Converts an int64 into an FOptionalInt64 automatically.
	 * @param Value The int64 to convert.
	 * @return An optional with the Int64 set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="Int64 To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalInt64 Conv_OptionalFromValue(int64 Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalInt64& Optional, int64& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's Int64 Value"))
	static int64 GetOptionalValue(const FOptionalInt64& Optional, int64 DefaultValue, bool& WasSet);

	
};
