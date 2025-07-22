
#include "BeamableCore/Public/AutoGen/MailSuccessResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMailSuccessResponseLibrary::MailSuccessResponseToJsonString(const UMailSuccessResponse* Serializable, const bool Pretty)
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

UMailSuccessResponse* UMailSuccessResponseLibrary::Make(bool bResult, UObject* Outer)
{
	auto Serializable = NewObject<UMailSuccessResponse>(Outer);
	Serializable->bResult = bResult;
	
	return Serializable;
}

void UMailSuccessResponseLibrary::Break(const UMailSuccessResponse* Serializable, bool& bResult)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bResult = Serializable->bResult;
	}
		
}

