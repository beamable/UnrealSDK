#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemCreateRequestBody.h"

#include "OptionalArrayOfItemCreateRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfItemCreateRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfItemCreateRequestBody struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UItemCreateRequestBody*>", NativeMakeFunc))
	static FOptionalArrayOfItemCreateRequestBody MakeOptional(TArray<UItemCreateRequestBody*> Value);

	/**
	 * @brief Converts an TArray<UItemCreateRequestBody*> into an FOptionalArrayOfItemCreateRequestBody automatically.
	 * @param Value The TArray<UItemCreateRequestBody*> to convert.
	 * @return An optional with the TArray<UItemCreateRequestBody*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Optionals", meta = (DisplayName="TArray<UItemCreateRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfItemCreateRequestBody Conv_OptionalFromValue(TArray<UItemCreateRequestBody*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|EventPlayers|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfItemCreateRequestBody& Optional, TArray<UItemCreateRequestBody*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UItemCreateRequestBody*> Value"))
	static TArray<UItemCreateRequestBody*> GetOptionalValue(const FOptionalArrayOfItemCreateRequestBody& Optional, TArray<UItemCreateRequestBody*> DefaultValue, bool& WasSet);

	
};
