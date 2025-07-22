
#include "BeamableCore/Public/AutoGen/PasswordUpdateRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPasswordUpdateRequestBodyLibrary::PasswordUpdateRequestBodyToJsonString(const UPasswordUpdateRequestBody* Serializable, const bool Pretty)
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

UPasswordUpdateRequestBody* UPasswordUpdateRequestBodyLibrary::Make(FString Email, FOptionalString CodeType, UObject* Outer)
{
	auto Serializable = NewObject<UPasswordUpdateRequestBody>(Outer);
	Serializable->Email = Email;
	Serializable->CodeType = CodeType;
	
	return Serializable;
}

void UPasswordUpdateRequestBodyLibrary::Break(const UPasswordUpdateRequestBody* Serializable, FString& Email, FOptionalString& CodeType)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Email = Serializable->Email;
		CodeType = Serializable->CodeType;
	}
		
}

