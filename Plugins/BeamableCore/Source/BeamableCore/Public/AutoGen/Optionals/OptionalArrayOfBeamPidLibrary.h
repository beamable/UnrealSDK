#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamPid.h"

#include "OptionalArrayOfBeamPidLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfBeamPidLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfBeamPid struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Make Optional TArray<FBeamPid>", NativeMakeFunc))
	static FOptionalArrayOfBeamPid MakeOptional(TArray<FBeamPid> Value);

	/**
	 * @brief Converts an TArray<FBeamPid> into an FOptionalArrayOfBeamPid automatically.
	 * @param Value The TArray<FBeamPid> to convert.
	 * @return An optional with the TArray<FBeamPid> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta = (DisplayName="TArray<FBeamPid> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfBeamPid Conv_OptionalFromValue(TArray<FBeamPid> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfBeamPid& Optional, TArray<FBeamPid>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<FBeamPid> Value"))
	static TArray<FBeamPid> GetOptionalValue(const FOptionalArrayOfBeamPid& Optional, TArray<FBeamPid> DefaultValue, bool& WasSet);

	
};
