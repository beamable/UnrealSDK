#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArchetypeProxy.h"

#include "OptionalArchetypeProxyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArchetypeProxyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArchetypeProxy struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Make Optional ArchetypeProxy", NativeMakeFunc))
	static FOptionalArchetypeProxy MakeOptional(UArchetypeProxy* Value);

	/**
	 * @brief Converts an UArchetypeProxy* into an FOptionalArchetypeProxy automatically.
	 * @param Value The UArchetypeProxy* to convert.
	 * @return An optional with the ArchetypeProxy set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta = (DisplayName = "Beam - ArchetypeProxy To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArchetypeProxy Conv_OptionalFromValue(UArchetypeProxy* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Optionals", meta=(DisplayName="Beam - Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArchetypeProxy& Optional, UArchetypeProxy*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Get Optional's ArchetypeProxy Value"))
	static UArchetypeProxy* GetOptionalValue(const FOptionalArchetypeProxy& Optional, UArchetypeProxy* DefaultValue, bool& WasSet);

	
};
