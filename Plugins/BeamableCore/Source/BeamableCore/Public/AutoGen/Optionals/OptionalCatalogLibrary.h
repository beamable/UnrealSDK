#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalCatalog.h"

#include "OptionalCatalogLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalCatalogLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalCatalog struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Optionals", meta=(DisplayName="Make Optional Catalog", NativeMakeFunc))
	static FOptionalCatalog MakeOptional(UCatalog* Value);

	/**
	 * @brief Converts an UCatalog* into an FOptionalCatalog automatically.
	 * @param Value The UCatalog* to convert.
	 * @return An optional with the Catalog set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Optionals", meta = (DisplayName="Catalog To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalCatalog Conv_OptionalFromValue(UCatalog* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Commerce|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalCatalog& Optional, UCatalog*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Optionals", meta=(DisplayName="Get Optional's Catalog Value"))
	static UCatalog* GetOptionalValue(const FOptionalCatalog& Optional, UCatalog* DefaultValue, bool& WasSet);

	
};
