#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSessionUser.h"

#include "OptionalSessionUserLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalSessionUserLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalSessionUser struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Optionals", meta=(DisplayName="Make Optional SessionUser", NativeMakeFunc))
	static FOptionalSessionUser MakeOptional(USessionUser* Value);

	/**
	 * @brief Converts an USessionUser* into an FOptionalSessionUser automatically.
	 * @param Value The USessionUser* to convert.
	 * @return An optional with the SessionUser set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Optionals", meta = (DisplayName="SessionUser To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalSessionUser Conv_OptionalFromValue(USessionUser* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Session|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalSessionUser& Optional, USessionUser*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Optionals", meta=(DisplayName="Get Optional's SessionUser Value"))
	static USessionUser* GetOptionalValue(const FOptionalSessionUser& Optional, USessionUser* DefaultValue, bool& WasSet);

	
};
