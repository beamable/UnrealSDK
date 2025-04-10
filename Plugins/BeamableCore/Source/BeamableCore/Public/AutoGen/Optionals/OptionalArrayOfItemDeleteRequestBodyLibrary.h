#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfItemDeleteRequestBody.h"

#include "OptionalArrayOfItemDeleteRequestBodyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfItemDeleteRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfItemDeleteRequestBody struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UItemDeleteRequestBody*>", NativeMakeFunc))
	static FOptionalArrayOfItemDeleteRequestBody MakeOptional(TArray<UItemDeleteRequestBody*> Value);

	/**
	 * @brief Converts an TArray<UItemDeleteRequestBody*> into an FOptionalArrayOfItemDeleteRequestBody automatically.
	 * @param Value The TArray<UItemDeleteRequestBody*> to convert.
	 * @return An optional with the TArray<UItemDeleteRequestBody*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta = (DisplayName="TArray<UItemDeleteRequestBody*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfItemDeleteRequestBody Conv_OptionalFromValue(TArray<UItemDeleteRequestBody*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfItemDeleteRequestBody& Optional, TArray<UItemDeleteRequestBody*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Inventory|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UItemDeleteRequestBody*> Value"))
	static TArray<UItemDeleteRequestBody*> GetOptionalValue(const FOptionalArrayOfItemDeleteRequestBody& Optional, TArray<UItemDeleteRequestBody*> DefaultValue, bool& WasSet);

	
};
