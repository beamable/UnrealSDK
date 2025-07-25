
#include "BeamableCore/Public/AutoGen/GetGroupStatusRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetGroupStatusRequestBodyLibrary::GetGroupStatusRequestBodyToJsonString(const UGetGroupStatusRequestBody* Serializable, const bool Pretty)
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

UGetGroupStatusRequestBody* UGetGroupStatusRequestBodyLibrary::Make(FOptionalString ContentId, UObject* Outer)
{
	auto Serializable = NewObject<UGetGroupStatusRequestBody>(Outer);
	Serializable->ContentId = ContentId;
	
	return Serializable;
}

void UGetGroupStatusRequestBodyLibrary::Break(const UGetGroupStatusRequestBody* Serializable, FOptionalString& ContentId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentId = Serializable->ContentId;
	}
		
}

