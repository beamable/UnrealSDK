#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalEventPlayerPhaseView.h"

#include "OptionalEventPlayerPhaseViewLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalEventPlayerPhaseViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalEventPlayerPhaseView struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Optionals", meta=(DisplayName="Make Optional EventPlayerPhaseView", NativeMakeFunc))
	static FOptionalEventPlayerPhaseView MakeOptional(UEventPlayerPhaseView* Value);

	/**
	 * @brief Converts an UEventPlayerPhaseView* into an FOptionalEventPlayerPhaseView automatically.
	 * @param Value The UEventPlayerPhaseView* to convert.
	 * @return An optional with the EventPlayerPhaseView set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Optionals", meta = (DisplayName="EventPlayerPhaseView To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalEventPlayerPhaseView Conv_OptionalFromValue(UEventPlayerPhaseView* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|EventPlayers|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalEventPlayerPhaseView& Optional, UEventPlayerPhaseView*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|EventPlayers|Utils|Optionals", meta=(DisplayName="Get Optional's EventPlayerPhaseView Value"))
	static UEventPlayerPhaseView* GetOptionalValue(const FOptionalEventPlayerPhaseView& Optional, UEventPlayerPhaseView* DefaultValue, bool& WasSet);

	
};
