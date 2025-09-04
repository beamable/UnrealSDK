#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalServicePlanActorServiceLimits.h"

#include "OptionalServicePlanActorServiceLimitsLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalServicePlanActorServiceLimitsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalServicePlanActorServiceLimits struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Optionals", meta=(DisplayName="Make Optional ServicePlanActorServiceLimits", NativeMakeFunc))
	static FOptionalServicePlanActorServiceLimits MakeOptional(UServicePlanActorServiceLimits* Value);

	/**
	 * @brief Converts an UServicePlanActorServiceLimits* into an FOptionalServicePlanActorServiceLimits automatically.
	 * @param Value The UServicePlanActorServiceLimits* to convert.
	 * @return An optional with the ServicePlanActorServiceLimits set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Optionals", meta = (DisplayName="ServicePlanActorServiceLimits To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalServicePlanActorServiceLimits Conv_OptionalFromValue(UServicePlanActorServiceLimits* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|ServicePlan|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalServicePlanActorServiceLimits& Optional, UServicePlanActorServiceLimits*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|ServicePlan|Utils|Optionals", meta=(DisplayName="Get Optional's ServicePlanActorServiceLimits Value"))
	static UServicePlanActorServiceLimits* GetOptionalValue(const FOptionalServicePlanActorServiceLimits& Optional, UServicePlanActorServiceLimits* DefaultValue, bool& WasSet);

	
};
