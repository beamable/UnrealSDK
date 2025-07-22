
#include "BeamableCore/Public/AutoGen/PasswordUpdateConfirmationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPasswordUpdateConfirmationLibrary::PasswordUpdateConfirmationToJsonString(const UPasswordUpdateConfirmation* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UPasswordUpdateConfirmation* UPasswordUpdateConfirmationLibrary::Make(FString Code, FString NewPassword, FOptionalString Email, UObject* Outer)
{
	auto Serializable = NewObject<UPasswordUpdateConfirmation>(Outer);
	Serializable->Code = Code;
	Serializable->NewPassword = NewPassword;
	Serializable->Email = Email;
	
	return Serializable;
}

void UPasswordUpdateConfirmationLibrary::Break(const UPasswordUpdateConfirmation* Serializable, FString& Code, FString& NewPassword, FOptionalString& Email)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Code = Serializable->Code;
		NewPassword = Serializable->NewPassword;
		Email = Serializable->Email;
	}
		
}

