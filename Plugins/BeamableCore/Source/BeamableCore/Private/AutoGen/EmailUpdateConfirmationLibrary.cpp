
#include "BeamableCore/Public/AutoGen/EmailUpdateConfirmationLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEmailUpdateConfirmationLibrary::EmailUpdateConfirmationToJsonString(const UEmailUpdateConfirmation* Serializable, const bool Pretty)
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

UEmailUpdateConfirmation* UEmailUpdateConfirmationLibrary::Make(FString Code, FString Password, UObject* Outer)
{
	auto Serializable = NewObject<UEmailUpdateConfirmation>(Outer);
	Serializable->Code = Code;
	Serializable->Password = Password;
	
	return Serializable;
}

void UEmailUpdateConfirmationLibrary::Break(const UEmailUpdateConfirmation* Serializable, FString& Code, FString& Password)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Code = Serializable->Code;
		Password = Serializable->Password;
	}
		
}

