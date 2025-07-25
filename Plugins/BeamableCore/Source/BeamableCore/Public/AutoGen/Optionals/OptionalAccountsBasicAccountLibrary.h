#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalAccountsBasicAccount.h"

#include "OptionalAccountsBasicAccountLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalAccountsBasicAccountLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalAccountsBasicAccount struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Optionals", meta=(DisplayName="Make Optional AccountsBasicAccount", NativeMakeFunc))
	static FOptionalAccountsBasicAccount MakeOptional(UAccountsBasicAccount* Value);

	/**
	 * @brief Converts an UAccountsBasicAccount* into an FOptionalAccountsBasicAccount automatically.
	 * @param Value The UAccountsBasicAccount* to convert.
	 * @return An optional with the AccountsBasicAccount set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Optionals", meta = (DisplayName="AccountsBasicAccount To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalAccountsBasicAccount Conv_OptionalFromValue(UAccountsBasicAccount* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Accounts|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalAccountsBasicAccount& Optional, UAccountsBasicAccount*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Accounts|Utils|Optionals", meta=(DisplayName="Get Optional's AccountsBasicAccount Value"))
	static UAccountsBasicAccount* GetOptionalValue(const FOptionalAccountsBasicAccount& Optional, UAccountsBasicAccount* DefaultValue, bool& WasSet);

	
};
