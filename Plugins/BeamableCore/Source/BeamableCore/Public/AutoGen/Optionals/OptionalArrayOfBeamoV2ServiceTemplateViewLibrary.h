#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoV2ServiceTemplateView.h"

#include "OptionalArrayOfBeamoV2ServiceTemplateViewLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfBeamoV2ServiceTemplateViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfBeamoV2ServiceTemplateView struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UBeamoV2ServiceTemplateView*>", NativeMakeFunc))
	static FOptionalArrayOfBeamoV2ServiceTemplateView MakeOptional(TArray<UBeamoV2ServiceTemplateView*> Value);

	/**
	 * @brief Converts an TArray<UBeamoV2ServiceTemplateView*> into an FOptionalArrayOfBeamoV2ServiceTemplateView automatically.
	 * @param Value The TArray<UBeamoV2ServiceTemplateView*> to convert.
	 * @return An optional with the TArray<UBeamoV2ServiceTemplateView*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="TArray<UBeamoV2ServiceTemplateView*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfBeamoV2ServiceTemplateView Conv_OptionalFromValue(TArray<UBeamoV2ServiceTemplateView*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfBeamoV2ServiceTemplateView& Optional, TArray<UBeamoV2ServiceTemplateView*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UBeamoV2ServiceTemplateView*> Value"))
	static TArray<UBeamoV2ServiceTemplateView*> GetOptionalValue(const FOptionalArrayOfBeamoV2ServiceTemplateView& Optional, TArray<UBeamoV2ServiceTemplateView*> DefaultValue, bool& WasSet);

	
};
