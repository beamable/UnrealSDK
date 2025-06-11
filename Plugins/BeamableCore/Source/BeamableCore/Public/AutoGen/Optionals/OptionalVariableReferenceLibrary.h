#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalVariableReference.h"

#include "OptionalVariableReferenceLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalVariableReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalVariableReference struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Make Optional VariableReference", NativeMakeFunc))
	static FOptionalVariableReference MakeOptional(UVariableReference* Value);

	/**
	 * @brief Converts an UVariableReference* into an FOptionalVariableReference automatically.
	 * @param Value The UVariableReference* to convert.
	 * @return An optional with the VariableReference set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta = (DisplayName="VariableReference To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalVariableReference Conv_OptionalFromValue(UVariableReference* Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalVariableReference& Optional, UVariableReference*& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Get Optional's VariableReference Value"))
	static UVariableReference* GetOptionalValue(const FOptionalVariableReference& Optional, UVariableReference* DefaultValue, bool& WasSet);

	
};
