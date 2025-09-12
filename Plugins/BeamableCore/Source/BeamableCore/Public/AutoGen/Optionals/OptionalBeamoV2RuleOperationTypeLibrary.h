#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2RuleOperationType.h"

#include "OptionalBeamoV2RuleOperationTypeLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamoV2RuleOperationTypeLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalBeamoV2RuleOperationType struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional BeamBeamoV2RuleOperationType", NativeMakeFunc))
	static FOptionalBeamoV2RuleOperationType MakeOptional(EBeamBeamoV2RuleOperationType Value);

	/**
	 * @brief Converts an EBeamBeamoV2RuleOperationType into an FOptionalBeamoV2RuleOperationType automatically.
	 * @param Value The EBeamBeamoV2RuleOperationType to convert.
	 * @return An optional with the BeamBeamoV2RuleOperationType set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="BeamBeamoV2RuleOperationType To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamoV2RuleOperationType Conv_OptionalFromValue(EBeamBeamoV2RuleOperationType Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamoV2RuleOperationType& Optional, EBeamBeamoV2RuleOperationType& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's BeamBeamoV2RuleOperationType Value"))
	static EBeamBeamoV2RuleOperationType GetOptionalValue(const FOptionalBeamoV2RuleOperationType& Optional, EBeamBeamoV2RuleOperationType DefaultValue, bool& WasSet);

	
};
