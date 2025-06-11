#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfRankEntryStat.h"

#include "OptionalArrayOfRankEntryStatLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfRankEntryStatLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfRankEntryStat struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Optionals", meta=(DisplayName="Make Optional TArray<URankEntryStat*>", NativeMakeFunc))
	static FOptionalArrayOfRankEntryStat MakeOptional(TArray<URankEntryStat*> Value);

	/**
	 * @brief Converts an TArray<URankEntryStat*> into an FOptionalArrayOfRankEntryStat automatically.
	 * @param Value The TArray<URankEntryStat*> to convert.
	 * @return An optional with the TArray<URankEntryStat*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Optionals", meta = (DisplayName="TArray<URankEntryStat*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfRankEntryStat Conv_OptionalFromValue(TArray<URankEntryStat*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Leaderboards|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfRankEntryStat& Optional, TArray<URankEntryStat*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<URankEntryStat*> Value"))
	static TArray<URankEntryStat*> GetOptionalValue(const FOptionalArrayOfRankEntryStat& Optional, TArray<URankEntryStat*> DefaultValue, bool& WasSet);

	
};
