#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMessage.h"

#include "OptionalMessageLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalMessageLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalMessage struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Optionals", meta=(DisplayName="Make Optional Message", NativeMakeFunc))
	static FOptionalMessage MakeOptional(UMessage* Value);

	/**
	 * @brief Converts an UMessage* into an FOptionalMessage automatically.
	 * @param Value The UMessage* to convert.
	 * @return An optional with the Message set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Optionals", meta = (DisplayName="Message To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalMessage Conv_OptionalFromValue(UMessage* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Mail|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalMessage& Optional, UMessage*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Mail|Utils|Optionals", meta=(DisplayName="Get Optional's Message Value"))
	static UMessage* GetOptionalValue(const FOptionalMessage& Optional, UMessage* DefaultValue, bool& WasSet);

	
};
