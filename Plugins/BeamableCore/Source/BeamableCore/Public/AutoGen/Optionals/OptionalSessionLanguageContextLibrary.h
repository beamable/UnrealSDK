#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSessionLanguageContext.h"

#include "OptionalSessionLanguageContextLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalSessionLanguageContextLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalSessionLanguageContext struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Optionals", meta=(DisplayName="Make Optional SessionLanguageContext", NativeMakeFunc))
	static FOptionalSessionLanguageContext MakeOptional(USessionLanguageContext* Value);

	/**
	 * @brief Converts an USessionLanguageContext* into an FOptionalSessionLanguageContext automatically.
	 * @param Value The USessionLanguageContext* to convert.
	 * @return An optional with the SessionLanguageContext set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Optionals", meta = (DisplayName="SessionLanguageContext To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalSessionLanguageContext Conv_OptionalFromValue(USessionLanguageContext* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Session|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalSessionLanguageContext& Optional, USessionLanguageContext*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Session|Utils|Optionals", meta=(DisplayName="Get Optional's SessionLanguageContext Value"))
	static USessionLanguageContext* GetOptionalValue(const FOptionalSessionLanguageContext& Optional, USessionLanguageContext* DefaultValue, bool& WasSet);

	
};
