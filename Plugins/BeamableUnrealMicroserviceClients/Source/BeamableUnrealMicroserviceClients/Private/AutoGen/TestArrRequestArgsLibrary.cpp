
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/TestArrRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UTestArrRequestArgsLibrary::TestArrRequestArgsToJsonString(const UTestArrRequestArgs* Serializable, const bool Pretty)
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

UTestArrRequestArgs* UTestArrRequestArgsLibrary::Make(int32 A, int32 B, UObject* Outer)
{
	auto Serializable = NewObject<UTestArrRequestArgs>(Outer);
	Serializable->A = A;
	Serializable->B = B;
	
	return Serializable;
}

void UTestArrRequestArgsLibrary::Break(const UTestArrRequestArgs* Serializable, int32& A, int32& B)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		A = Serializable->A;
		B = Serializable->B;
	}
		
}

