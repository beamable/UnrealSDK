#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMetadataView.h"

#include "OptionalMetadataViewLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMetadataViewLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalMetadataView struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Optionals", meta=(DisplayName="Make Optional MetadataView", NativeMakeFunc))
	static FOptionalMetadataView MakeOptional(UMetadataView* Value);

	/**
	 * @brief Converts an UMetadataView* into an FOptionalMetadataView automatically.
	 * @param Value The UMetadataView* to convert.
	 * @return An optional with the MetadataView set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Optionals", meta = (DisplayName="MetadataView To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalMetadataView Conv_OptionalFromValue(UMetadataView* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Leaderboards|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalMetadataView& Optional, UMetadataView*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Leaderboards|Utils|Optionals", meta=(DisplayName="Get Optional's MetadataView Value"))
	static UMetadataView* GetOptionalValue(const FOptionalMetadataView& Optional, UMetadataView* DefaultValue, bool& WasSet);

	
};
