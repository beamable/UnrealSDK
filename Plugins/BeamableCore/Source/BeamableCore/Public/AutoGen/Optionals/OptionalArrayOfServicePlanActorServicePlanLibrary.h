#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServicePlanActorServicePlan.h"

#include "OptionalArrayOfServicePlanActorServicePlanLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfServicePlanActorServicePlanLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfServicePlanActorServicePlan struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UServicePlanActorServicePlan*>", NativeMakeFunc))
	static FOptionalArrayOfServicePlanActorServicePlan MakeOptional(TArray<UServicePlanActorServicePlan*> Value);

	/**
	 * @brief Converts an TArray<UServicePlanActorServicePlan*> into an FOptionalArrayOfServicePlanActorServicePlan automatically.
	 * @param Value The TArray<UServicePlanActorServicePlan*> to convert.
	 * @return An optional with the TArray<UServicePlanActorServicePlan*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Optionals", meta = (DisplayName="TArray<UServicePlanActorServicePlan*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfServicePlanActorServicePlan Conv_OptionalFromValue(TArray<UServicePlanActorServicePlan*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|ServicePlan|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfServicePlanActorServicePlan& Optional, TArray<UServicePlanActorServicePlan*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UServicePlanActorServicePlan*> Value"))
	static TArray<UServicePlanActorServicePlan*> GetOptionalValue(const FOptionalArrayOfServicePlanActorServicePlan& Optional, TArray<UServicePlanActorServicePlan*> DefaultValue, bool& WasSet);

	
};
