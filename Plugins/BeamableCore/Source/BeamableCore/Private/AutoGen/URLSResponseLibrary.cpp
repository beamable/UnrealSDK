
#include "BeamableCore/Public/AutoGen/URLSResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UURLSResponseLibrary::URLSResponseToJsonString(const UURLSResponse* Serializable, const bool Pretty)
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

UURLSResponse* UURLSResponseLibrary::Make(TArray<UCloudsavingBasicURLResponse*> Response, UObject* Outer)
{
	auto Serializable = NewObject<UURLSResponse>(Outer);
	Serializable->Response = Response;
	
	return Serializable;
}

void UURLSResponseLibrary::Break(const UURLSResponse* Serializable, TArray<UCloudsavingBasicURLResponse*>& Response)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Response = Serializable->Response;
	}
		
}

