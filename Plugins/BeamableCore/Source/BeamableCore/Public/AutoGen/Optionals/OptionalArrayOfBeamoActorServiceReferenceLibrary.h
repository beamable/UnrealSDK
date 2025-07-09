#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamoActorServiceReference.h"

#include "OptionalArrayOfBeamoActorServiceReferenceLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfBeamoActorServiceReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfBeamoActorServiceReference struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UBeamoActorServiceReference*>", NativeMakeFunc))
	static FOptionalArrayOfBeamoActorServiceReference MakeOptional(TArray<UBeamoActorServiceReference*> Value);

	/**
	 * @brief Converts an TArray<UBeamoActorServiceReference*> into an FOptionalArrayOfBeamoActorServiceReference automatically.
	 * @param Value The TArray<UBeamoActorServiceReference*> to convert.
	 * @return An optional with the TArray<UBeamoActorServiceReference*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="TArray<UBeamoActorServiceReference*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfBeamoActorServiceReference Conv_OptionalFromValue(TArray<UBeamoActorServiceReference*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfBeamoActorServiceReference& Optional, TArray<UBeamoActorServiceReference*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UBeamoActorServiceReference*> Value"))
	static TArray<UBeamoActorServiceReference*> GetOptionalValue(const FOptionalArrayOfBeamoActorServiceReference& Optional, TArray<UBeamoActorServiceReference*> DefaultValue, bool& WasSet);

	
};
