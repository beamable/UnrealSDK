#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamPromotableType.h"

#include "OptionalArrayOfBeamPromotableTypeLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfBeamPromotableTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfBeamPromotableType struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Optionals", meta=(DisplayName="Make Optional TArray<EBeamPromotableType>", NativeMakeFunc))
	static FOptionalArrayOfBeamPromotableType MakeOptional(TArray<EBeamPromotableType> Value);

	/**
	 * @brief Converts an TArray<EBeamPromotableType> into an FOptionalArrayOfBeamPromotableType automatically.
	 * @param Value The TArray<EBeamPromotableType> to convert.
	 * @return An optional with the TArray<EBeamPromotableType> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Optionals", meta = (DisplayName="TArray<EBeamPromotableType> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfBeamPromotableType Conv_OptionalFromValue(TArray<EBeamPromotableType> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Customer|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfBeamPromotableType& Optional, TArray<EBeamPromotableType>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Customer|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<EBeamPromotableType> Value"))
	static TArray<EBeamPromotableType> GetOptionalValue(const FOptionalArrayOfBeamPromotableType& Optional, TArray<EBeamPromotableType> DefaultValue, bool& WasSet);

	
};
