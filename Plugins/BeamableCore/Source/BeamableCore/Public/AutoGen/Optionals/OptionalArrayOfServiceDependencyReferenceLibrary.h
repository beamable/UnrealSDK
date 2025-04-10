#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceDependencyReference.h"

#include "OptionalArrayOfServiceDependencyReferenceLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfServiceDependencyReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfServiceDependencyReference struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UServiceDependencyReference*>", NativeMakeFunc))
	static FOptionalArrayOfServiceDependencyReference MakeOptional(TArray<UServiceDependencyReference*> Value);

	/**
	 * @brief Converts an TArray<UServiceDependencyReference*> into an FOptionalArrayOfServiceDependencyReference automatically.
	 * @param Value The TArray<UServiceDependencyReference*> to convert.
	 * @return An optional with the TArray<UServiceDependencyReference*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="TArray<UServiceDependencyReference*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfServiceDependencyReference Conv_OptionalFromValue(TArray<UServiceDependencyReference*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfServiceDependencyReference& Optional, TArray<UServiceDependencyReference*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UServiceDependencyReference*> Value"))
	static TArray<UServiceDependencyReference*> GetOptionalValue(const FOptionalArrayOfServiceDependencyReference& Optional, TArray<UServiceDependencyReference*> DefaultValue, bool& WasSet);

	
};
