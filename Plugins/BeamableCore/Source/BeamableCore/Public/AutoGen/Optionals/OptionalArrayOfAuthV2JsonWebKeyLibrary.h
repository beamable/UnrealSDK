#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAuthV2JsonWebKey.h"

#include "OptionalArrayOfAuthV2JsonWebKeyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfAuthV2JsonWebKeyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfAuthV2JsonWebKey struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UAuthV2JsonWebKey*>", NativeMakeFunc))
	static FOptionalArrayOfAuthV2JsonWebKey MakeOptional(TArray<UAuthV2JsonWebKey*> Value);

	/**
	 * @brief Converts an TArray<UAuthV2JsonWebKey*> into an FOptionalArrayOfAuthV2JsonWebKey automatically.
	 * @param Value The TArray<UAuthV2JsonWebKey*> to convert.
	 * @return An optional with the TArray<UAuthV2JsonWebKey*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta = (DisplayName="TArray<UAuthV2JsonWebKey*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfAuthV2JsonWebKey Conv_OptionalFromValue(TArray<UAuthV2JsonWebKey*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfAuthV2JsonWebKey& Optional, TArray<UAuthV2JsonWebKey*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Auth|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UAuthV2JsonWebKey*> Value"))
	static TArray<UAuthV2JsonWebKey*> GetOptionalValue(const FOptionalArrayOfAuthV2JsonWebKey& Optional, TArray<UAuthV2JsonWebKey*> DefaultValue, bool& WasSet);

	
};
