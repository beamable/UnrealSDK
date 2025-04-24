#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfAttachmentProperty.h"

#include "OptionalArrayOfAttachmentPropertyLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfAttachmentPropertyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfAttachmentProperty struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UAttachmentProperty*>", NativeMakeFunc))
	static FOptionalArrayOfAttachmentProperty MakeOptional(TArray<UAttachmentProperty*> Value);

	/**
	 * @brief Converts an TArray<UAttachmentProperty*> into an FOptionalArrayOfAttachmentProperty automatically.
	 * @param Value The TArray<UAttachmentProperty*> to convert.
	 * @return An optional with the TArray<UAttachmentProperty*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta = (DisplayName="TArray<UAttachmentProperty*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfAttachmentProperty Conv_OptionalFromValue(TArray<UAttachmentProperty*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfAttachmentProperty& Optional, TArray<UAttachmentProperty*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|Announcements|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UAttachmentProperty*> Value"))
	static TArray<UAttachmentProperty*> GetOptionalValue(const FOptionalArrayOfAttachmentProperty& Optional, TArray<UAttachmentProperty*> DefaultValue, bool& WasSet);

	
};
