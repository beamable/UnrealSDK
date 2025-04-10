#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamoBasicManifestChecksum.h"

#include "OptionalBeamoBasicManifestChecksumLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamoBasicManifestChecksumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalBeamoBasicManifestChecksum struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Make Optional BeamoBasicManifestChecksum", NativeMakeFunc))
	static FOptionalBeamoBasicManifestChecksum MakeOptional(UBeamoBasicManifestChecksum* Value);

	/**
	 * @brief Converts an UBeamoBasicManifestChecksum* into an FOptionalBeamoBasicManifestChecksum automatically.
	 * @param Value The UBeamoBasicManifestChecksum* to convert.
	 * @return An optional with the BeamoBasicManifestChecksum set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta = (DisplayName="BeamoBasicManifestChecksum To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamoBasicManifestChecksum Conv_OptionalFromValue(UBeamoBasicManifestChecksum* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamoBasicManifestChecksum& Optional, UBeamoBasicManifestChecksum*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Optionals", meta=(DisplayName="Get Optional's BeamoBasicManifestChecksum Value"))
	static UBeamoBasicManifestChecksum* GetOptionalValue(const FOptionalBeamoBasicManifestChecksum& Optional, UBeamoBasicManifestChecksum* DefaultValue, bool& WasSet);

	
};
