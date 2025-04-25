#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalTournamentGroupEntry.h"

#include "OptionalTournamentGroupEntryLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalTournamentGroupEntryLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalTournamentGroupEntry struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Optionals", meta=(DisplayName="Make Optional TournamentGroupEntry", NativeMakeFunc))
	static FOptionalTournamentGroupEntry MakeOptional(UTournamentGroupEntry* Value);

	/**
	 * @brief Converts an UTournamentGroupEntry* into an FOptionalTournamentGroupEntry automatically.
	 * @param Value The UTournamentGroupEntry* to convert.
	 * @return An optional with the TournamentGroupEntry set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Optionals", meta = (DisplayName="TournamentGroupEntry To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalTournamentGroupEntry Conv_OptionalFromValue(UTournamentGroupEntry* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Tournaments|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalTournamentGroupEntry& Optional, UTournamentGroupEntry*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Tournaments|Utils|Optionals", meta=(DisplayName="Get Optional's TournamentGroupEntry Value"))
	static UTournamentGroupEntry* GetOptionalValue(const FOptionalTournamentGroupEntry& Optional, UTournamentGroupEntry* DefaultValue, bool& WasSet);

	
};
