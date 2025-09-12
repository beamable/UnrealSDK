#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoV2ObjectId.h"

#include "OptionalBeamoV2ObjectIdLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamoV2ObjectIdLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalBeamoV2ObjectId struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional BeamoV2ObjectId", NativeMakeFunc))
	static FOptionalBeamoV2ObjectId MakeOptional(UBeamoV2ObjectId* Value);

	/**
	 * @brief Converts an UBeamoV2ObjectId* into an FOptionalBeamoV2ObjectId automatically.
	 * @param Value The UBeamoV2ObjectId* to convert.
	 * @return An optional with the BeamoV2ObjectId set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="BeamoV2ObjectId To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamoV2ObjectId Conv_OptionalFromValue(UBeamoV2ObjectId* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamoV2ObjectId& Optional, UBeamoV2ObjectId*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's BeamoV2ObjectId Value"))
	static UBeamoV2ObjectId* GetOptionalValue(const FOptionalBeamoV2ObjectId& Optional, UBeamoV2ObjectId* DefaultValue, bool& WasSet);

	
};
