#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPresenceStatus.h"

#include "OptionalPresenceStatusLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalPresenceStatusLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalPresenceStatus struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Make Optional PresenceStatus", NativeMakeFunc))
	static FOptionalPresenceStatus MakeOptional(EPresenceStatus Value);

	/**
	 * @brief Converts an EPresenceStatus into an FOptionalPresenceStatus automatically.
	 * @param Value The EPresenceStatus to convert.
	 * @return An optional with the PresenceStatus set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta = (DisplayName = "Beam - PresenceStatus To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalPresenceStatus Conv_OptionalFromValue(EPresenceStatus Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Optionals", meta=(DisplayName="Beam - Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalPresenceStatus& Optional, EPresenceStatus& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Optionals", meta=(DisplayName="Beam - Get Optional's PresenceStatus Value"))
	static EPresenceStatus GetOptionalValue(const FOptionalPresenceStatus& Optional, EPresenceStatus DefaultValue, bool& WasSet);

	
};
