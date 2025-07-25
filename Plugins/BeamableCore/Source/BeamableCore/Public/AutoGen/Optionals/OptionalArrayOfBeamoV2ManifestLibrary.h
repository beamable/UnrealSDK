#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2Manifest.h"

#include "OptionalArrayOfBeamoV2ManifestLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfBeamoV2ManifestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfBeamoV2Manifest struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UBeamoV2Manifest*>", NativeMakeFunc))
	static FOptionalArrayOfBeamoV2Manifest MakeOptional(TArray<UBeamoV2Manifest*> Value);

	/**
	 * @brief Converts an TArray<UBeamoV2Manifest*> into an FOptionalArrayOfBeamoV2Manifest automatically.
	 * @param Value The TArray<UBeamoV2Manifest*> to convert.
	 * @return An optional with the TArray<UBeamoV2Manifest*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="TArray<UBeamoV2Manifest*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfBeamoV2Manifest Conv_OptionalFromValue(TArray<UBeamoV2Manifest*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfBeamoV2Manifest& Optional, TArray<UBeamoV2Manifest*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UBeamoV2Manifest*> Value"))
	static TArray<UBeamoV2Manifest*> GetOptionalValue(const FOptionalArrayOfBeamoV2Manifest& Optional, TArray<UBeamoV2Manifest*> DefaultValue, bool& WasSet);

	
};
