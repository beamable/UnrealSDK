#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2DataPoint.h"

#include "OptionalArrayOfBeamoV2DataPointLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfBeamoV2DataPointLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfBeamoV2DataPoint struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UBeamoV2DataPoint*>", NativeMakeFunc))
	static FOptionalArrayOfBeamoV2DataPoint MakeOptional(TArray<UBeamoV2DataPoint*> Value);

	/**
	 * @brief Converts an TArray<UBeamoV2DataPoint*> into an FOptionalArrayOfBeamoV2DataPoint automatically.
	 * @param Value The TArray<UBeamoV2DataPoint*> to convert.
	 * @return An optional with the TArray<UBeamoV2DataPoint*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="TArray<UBeamoV2DataPoint*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfBeamoV2DataPoint Conv_OptionalFromValue(TArray<UBeamoV2DataPoint*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfBeamoV2DataPoint& Optional, TArray<UBeamoV2DataPoint*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UBeamoV2DataPoint*> Value"))
	static TArray<UBeamoV2DataPoint*> GetOptionalValue(const FOptionalArrayOfBeamoV2DataPoint& Optional, TArray<UBeamoV2DataPoint*> DefaultValue, bool& WasSet);

	
};
