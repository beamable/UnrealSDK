#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPlayerStatRequirement.h"

#include "OptionalArrayOfPlayerStatRequirementLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfPlayerStatRequirementLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfPlayerStatRequirement struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UPlayerStatRequirement*>", NativeMakeFunc))
	static FOptionalArrayOfPlayerStatRequirement MakeOptional(TArray<UPlayerStatRequirement*> Value);

	/**
	 * @brief Converts an TArray<UPlayerStatRequirement*> into an FOptionalArrayOfPlayerStatRequirement automatically.
	 * @param Value The TArray<UPlayerStatRequirement*> to convert.
	 * @return An optional with the TArray<UPlayerStatRequirement*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta = (DisplayName="TArray<UPlayerStatRequirement*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfPlayerStatRequirement Conv_OptionalFromValue(TArray<UPlayerStatRequirement*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfPlayerStatRequirement& Optional, TArray<UPlayerStatRequirement*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UPlayerStatRequirement*> Value"))
	static TArray<UPlayerStatRequirement*> GetOptionalValue(const FOptionalArrayOfPlayerStatRequirement& Optional, TArray<UPlayerStatRequirement*> DefaultValue, bool& WasSet);

	
};
