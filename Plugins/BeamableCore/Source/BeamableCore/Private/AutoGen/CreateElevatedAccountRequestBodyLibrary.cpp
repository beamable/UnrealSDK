
#include "BeamableCore/Public/AutoGen/CreateElevatedAccountRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateElevatedAccountRequestBodyLibrary::CreateElevatedAccountRequestBodyToJsonString(const UCreateElevatedAccountRequestBody* Serializable, const bool Pretty)
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

UCreateElevatedAccountRequestBody* UCreateElevatedAccountRequestBodyLibrary::Make(FString Email, FOptionalString Role, FOptionalMapOfString InitProperties, UObject* Outer)
{
	auto Serializable = NewObject<UCreateElevatedAccountRequestBody>(Outer);
	Serializable->Email = Email;
	Serializable->Role = Role;
	Serializable->InitProperties = InitProperties;
	
	return Serializable;
}

void UCreateElevatedAccountRequestBodyLibrary::Break(const UCreateElevatedAccountRequestBody* Serializable, FString& Email, FOptionalString& Role, FOptionalMapOfString& InitProperties)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Email = Serializable->Email;
		Role = Serializable->Role;
		InitProperties = Serializable->InitProperties;
	}
		
}

