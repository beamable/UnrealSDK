#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamContentId.h"

#include "OptionalBeamContentIdLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalBeamContentIdLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalBeamContentId struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Optionals", meta=(DisplayName="Make Optional BeamContentId", NativeMakeFunc))
	static FOptionalBeamContentId MakeOptional(FBeamContentId Value);

	/**
	 * @brief Converts an FBeamContentId into an FOptionalBeamContentId automatically.
	 * @param Value The FBeamContentId to convert.
	 * @return An optional with the BeamContentId set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Optionals", meta = (DisplayName="BeamContentId To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalBeamContentId Conv_OptionalFromValue(FBeamContentId Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Lobby|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalBeamContentId& Optional, FBeamContentId& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Optionals", meta=(DisplayName="Get Optional's BeamContentId Value"))
	static FBeamContentId GetOptionalValue(const FOptionalBeamContentId& Optional, FBeamContentId DefaultValue, bool& WasSet);

	
};
