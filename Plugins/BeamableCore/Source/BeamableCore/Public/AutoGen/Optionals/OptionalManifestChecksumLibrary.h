

#pragma once

#include "CoreMinimal.h"
#include "AutoGen/Optionals/OptionalManifestChecksum.h"

#include "OptionalManifestChecksumLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalManifestChecksumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalManifestChecksum struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Make Optional ManifestChecksum", NativeMakeFunc))
	static FOptionalManifestChecksum MakeOptional(UManifestChecksum* Value);

	/**
	 * @brief Converts an UManifestChecksum* into an FOptionalManifestChecksum automatically.
	 * @param Value The UManifestChecksum* to convert.
	 * @return An optional with the ManifestChecksum set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta = (DisplayName = "Beam - ManifestChecksum To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalManifestChecksum Conv_OptionalFromValue(UManifestChecksum* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Optionals", meta=(DisplayName="Beam - Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalManifestChecksum& Optional, UManifestChecksum*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Get Optional's ManifestChecksum Value"))
	static UManifestChecksum* GetOptionalValue(const FOptionalManifestChecksum& Optional, UManifestChecksum* DefaultValue, bool& WasSet);

	
};
