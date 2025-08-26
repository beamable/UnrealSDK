#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceStorageStatus.h"

#include "OptionalArrayOfBeamoV2ServiceStorageStatusLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfBeamoV2ServiceStorageStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfBeamoV2ServiceStorageStatus struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UBeamoV2ServiceStorageStatus*>", NativeMakeFunc))
	static FOptionalArrayOfBeamoV2ServiceStorageStatus MakeOptional(TArray<UBeamoV2ServiceStorageStatus*> Value);

	/**
	 * @brief Converts an TArray<UBeamoV2ServiceStorageStatus*> into an FOptionalArrayOfBeamoV2ServiceStorageStatus automatically.
	 * @param Value The TArray<UBeamoV2ServiceStorageStatus*> to convert.
	 * @return An optional with the TArray<UBeamoV2ServiceStorageStatus*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="TArray<UBeamoV2ServiceStorageStatus*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfBeamoV2ServiceStorageStatus Conv_OptionalFromValue(TArray<UBeamoV2ServiceStorageStatus*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfBeamoV2ServiceStorageStatus& Optional, TArray<UBeamoV2ServiceStorageStatus*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UBeamoV2ServiceStorageStatus*> Value"))
	static TArray<UBeamoV2ServiceStorageStatus*> GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceStorageStatus& Optional, TArray<UBeamoV2ServiceStorageStatus*> DefaultValue, bool& WasSet);

	
};
