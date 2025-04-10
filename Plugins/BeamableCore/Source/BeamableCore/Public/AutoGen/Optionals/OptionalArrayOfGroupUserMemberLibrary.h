#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfGroupUserMember.h"

#include "OptionalArrayOfGroupUserMemberLibrary.generated.h"

UCLASS(BlueprintType)
class BEAMABLECORE_API UOptionalArrayOfGroupUserMemberLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:	

	/**
	* @brief Constructs an FOptionalArrayOfGroupUserMember struct from the given value.	  
	*/
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Make Optional TArray<UGroupUserMember*>", NativeMakeFunc))
	static FOptionalArrayOfGroupUserMember MakeOptional(TArray<UGroupUserMember*> Value);

	/**
	 * @brief Converts an TArray<UGroupUserMember*> into an FOptionalArrayOfGroupUserMember automatically.
	 * @param Value The TArray<UGroupUserMember*> to convert.
	 * @return An optional with the TArray<UGroupUserMember*> set as it's value.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta = (DisplayName="TArray<UGroupUserMember*> To Optional", CompactNodeTitle = "->", BlueprintAutocast))
	static FOptionalArrayOfGroupUserMember Conv_OptionalFromValue(TArray<UGroupUserMember*> Value);
	
	/**
	 * @brief Use this when the behavior changes based on whether or not a value is set on the optional.
	 * @param Optional The optional you wish to get data from.
	 * @param Value The value in the optional. 
	 * @return Whether or not the value was set. We provide no guarantees on what the value is if the optional is not set. 
	 */
	UFUNCTION(BlueprintCallable, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Optional Has Value", ExpandBoolAsExecs="ReturnValue"))
	static bool HasValue(const FOptionalArrayOfGroupUserMember& Optional, TArray<UGroupUserMember*>& Value);

	/**
	 * @brief Use this when the behaviour doesnt change based on whether or not the value is set, instead just provide a default value instead.
	 * @param Optional The optional you wish to get data from.
	 * @param DefaultValue The value that will be set if the Optional has no value in it.
	 * @param WasSet Whether or not the value was set. When false, the return value is the given DefaultValue.   
	 * @return The default value, if the Optional IS NOT set. The optional value, otherwise.
	 */
	UFUNCTION(BlueprintPure, Category="Beam|GroupUsers|Utils|Optionals", meta=(DisplayName="Get Optional's TArray<UGroupUserMember*> Value"))
	static TArray<UGroupUserMember*> GetOptionalValue(const FOptionalArrayOfGroupUserMember& Optional, TArray<UGroupUserMember*> DefaultValue, bool& WasSet);

	
};
