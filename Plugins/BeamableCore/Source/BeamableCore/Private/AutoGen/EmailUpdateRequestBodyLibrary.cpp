
#include "BeamableCore/Public/AutoGen/EmailUpdateRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEmailUpdateRequestBodyLibrary::EmailUpdateRequestBodyToJsonString(const UEmailUpdateRequestBody* Serializable, const bool Pretty)
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

UEmailUpdateRequestBody* UEmailUpdateRequestBodyLibrary::Make(FString NewEmail, FOptionalString CodeType, UObject* Outer)
{
	auto Serializable = NewObject<UEmailUpdateRequestBody>(Outer);
	Serializable->NewEmail = NewEmail;
	Serializable->CodeType = CodeType;
	
	return Serializable;
}

void UEmailUpdateRequestBodyLibrary::Break(const UEmailUpdateRequestBody* Serializable, FString& NewEmail, FOptionalString& CodeType)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		NewEmail = Serializable->NewEmail;
		CodeType = Serializable->CodeType;
	}
		
}

