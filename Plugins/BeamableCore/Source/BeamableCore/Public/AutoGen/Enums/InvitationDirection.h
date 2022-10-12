
#pragma once

#include "CoreMinimal.h"

#include "InvitationDirection.generated.h"

UENUM(BlueprintType)
enum class EInvitationDirection : uint8
{
	Incoming UMETA(DisplayName="Incoming", SerializationName="incoming"),
	Outgoing UMETA(DisplayName="Outgoing", SerializationName="outgoing")		
};

UCLASS(BlueprintType)
class UInvitationDirectionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:		
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "InvitationDirection To Serialization Name", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static FString InvitationDirectionToSerializationName(EInvitationDirection Value)
	{
		const UEnum* Enum = StaticEnum<EInvitationDirection>();
		const int32 NameIndex = Enum->GetIndexByValue(static_cast<int64>(Value));
		const FString SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);		
		return SerializationName;
		
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Serialization Name To InvitationDirection", CompactNodeTitle = "->"), Category="Beam Enum Converters")
	static EInvitationDirection SerializationNameToInvitationDirection(FString Value)
	{
		const UEnum* Enum = StaticEnum<EInvitationDirection>();
		for (int32 NameIndex = 0; NameIndex < Enum->NumEnums() - 1; ++NameIndex)
		{
			const FString& SerializationName = Enum->GetMetaData(TEXT("SerializationName"), NameIndex);
			if(Value == SerializationName)
				return static_cast<EInvitationDirection>(Enum->GetValueByIndex(NameIndex));
		}
		
		ensureAlways(false); //  This should be impossible!
		return EInvitationDirection();
	}	
};

