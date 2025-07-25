
#include "BeamableCore/Public/AutoGen/LambdaResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString ULambdaResponseLibrary::LambdaResponseToJsonString(const ULambdaResponse* Serializable, const bool Pretty)
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

ULambdaResponse* ULambdaResponseLibrary::Make(int32 StatusCode, FOptionalString Body, UObject* Outer)
{
	auto Serializable = NewObject<ULambdaResponse>(Outer);
	Serializable->StatusCode = StatusCode;
	Serializable->Body = Body;
	
	return Serializable;
}

void ULambdaResponseLibrary::Break(const ULambdaResponse* Serializable, int32& StatusCode, FOptionalString& Body)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		StatusCode = Serializable->StatusCode;
		Body = Serializable->Body;
	}
		
}

