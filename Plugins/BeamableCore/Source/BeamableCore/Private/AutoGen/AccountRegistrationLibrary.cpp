
#include "BeamableCore/Public/AutoGen/AccountRegistrationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAccountRegistrationLibrary::AccountRegistrationToJsonString(const UAccountRegistration* Serializable, const bool Pretty)
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

UAccountRegistration* UAccountRegistrationLibrary::Make(FString Email, FString Password, UObject* Outer)
{
	auto Serializable = NewObject<UAccountRegistration>(Outer);
	Serializable->Email = Email;
	Serializable->Password = Password;
	
	return Serializable;
}

void UAccountRegistrationLibrary::Break(const UAccountRegistration* Serializable, FString& Email, FString& Password)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Email = Serializable->Email;
		Password = Serializable->Password;
	}
		
}

