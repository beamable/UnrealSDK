#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRedisShard.h"

#include "OptionalArrayOfRedisShardLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfRedisShardLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfRedisShard struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Make Optional TArray<URedisShard*>", NativeMakeFunc))
	static FOptionalArrayOfRedisShard MakeOptional(TArray<URedisShard*> Value);

	/**
	 * @brief Converts an TArray<URedisShard*> into an FOptionalArrayOfRedisShard automatically.
	 * @param Value The TArray<URedisShard*> to convert.
	 * @return An optional with the TArray<URedisShard*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta = (DisplayName="TArray<URedisShard*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfRedisShard Conv_OptionalFromValue(TArray<URedisShard*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfRedisShard& Optional, TArray<URedisShard*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<URedisShard*> Value"))
	static TArray<URedisShard*> GetOptionalValue(const FOptionalArrayOfRedisShard& Optional, TArray<URedisShard*> DefaultValue, bool& WasSet);

	
};
