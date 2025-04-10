#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfPartyInvitation.h"

#include "OptionalArrayOfPartyInvitationLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfPartyInvitationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfPartyInvitation struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UPartyInvitation*>", NativeMakeFunc))
	static FOptionalArrayOfPartyInvitation MakeOptional(TArray<UPartyInvitation*> Value);

	/**
	 * @brief Converts an TArray<UPartyInvitation*> into an FOptionalArrayOfPartyInvitation automatically.
	 * @param Value The TArray<UPartyInvitation*> to convert.
	 * @return An optional with the TArray<UPartyInvitation*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Optionals", meta = (DisplayName="TArray<UPartyInvitation*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfPartyInvitation Conv_OptionalFromValue(TArray<UPartyInvitation*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Party|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfPartyInvitation& Optional, TArray<UPartyInvitation*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Party|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UPartyInvitation*> Value"))
	static TArray<UPartyInvitation*> GetOptionalValue(const FOptionalArrayOfPartyInvitation& Optional, TArray<UPartyInvitation*> DefaultValue, bool& WasSet);

	
};
