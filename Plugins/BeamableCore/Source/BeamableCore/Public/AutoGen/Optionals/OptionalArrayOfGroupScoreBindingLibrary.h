#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfGroupScoreBinding.h"

#include "OptionalArrayOfGroupScoreBindingLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfGroupScoreBindingLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfGroupScoreBinding struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UGroupScoreBinding*>", NativeMakeFunc))
	static FOptionalArrayOfGroupScoreBinding MakeOptional(TArray<UGroupScoreBinding*> Value);

	/**
	 * @brief Converts an TArray<UGroupScoreBinding*> into an FOptionalArrayOfGroupScoreBinding automatically.
	 * @param Value The TArray<UGroupScoreBinding*> to convert.
	 * @return An optional with the TArray<UGroupScoreBinding*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta = (DisplayName="TArray<UGroupScoreBinding*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfGroupScoreBinding Conv_OptionalFromValue(TArray<UGroupScoreBinding*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfGroupScoreBinding& Optional, TArray<UGroupScoreBinding*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UGroupScoreBinding*> Value"))
	static TArray<UGroupScoreBinding*> GetOptionalValue(const FOptionalArrayOfGroupScoreBinding& Optional, TArray<UGroupScoreBinding*> DefaultValue, bool& WasSet);

	
};
