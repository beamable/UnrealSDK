
#include "BeamableCore/Public/AutoGen/RenameRealmRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URenameRealmRequestBodyLibrary::RenameRealmRequestBodyToJsonString(const URenameRealmRequestBody* Serializable, const bool Pretty)
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

URenameRealmRequestBody* URenameRealmRequestBodyLibrary::Make(FString NewName, UObject* Outer)
{
	auto Serializable = NewObject<URenameRealmRequestBody>(Outer);
	Serializable->NewName = NewName;
	
	return Serializable;
}

void URenameRealmRequestBodyLibrary::Break(const URenameRealmRequestBody* Serializable, FString& NewName)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		NewName = Serializable->NewName;
	}
		
}

